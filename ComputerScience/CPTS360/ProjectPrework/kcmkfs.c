/***************************************************************
   KCW: make ext2 filesystem on 1.44MB floppy disk (11-4-97)
***************************************************************/
#include <sys/types.h>
#include <fcntl.h>
#include <linux/ext2_fs.h>

#define BLK 1024

typedef struct ext2_super_block SUPER;
typedef struct ext2_group_desc  GD;
typedef struct ext2_inode       INODE;
typedef struct ext2_dir_entry_2 DIR;

SUPER *sp;
GD    *gp;
INODE *ip;
DIR   *dp;

char buf[BLK], *cp;

int  fd, i, j, n, r;
int  nblocks, ninodes;
int BLOCK;
int  ngroups, ngblocks;
int  bmap, imap, inodes_start, inodes_blocks, root_block;

int  used_blocks, used_inodes;
int  free_blocks, free_inodes;


int get_block(int block, char *buf)
{
    lseek(fd, (long)(BLK *  block), 0);
	return read(buf, fd, BLK);
}	

int put_block(int block, char *buf)
{
    lseek(fd, (long)(BLK *  block), 0);
	return write(fd, buf, BLK);
}

int set_bit(char *c, int bit)
{
  buf[bit/8] |=  (1 << bit%8);
}

int clr_bit(char *c, int bit)
{
  buf[bit/8] &= ~(1 << bit%8);
}

int make_bmap()
{
	int i=0;
	set_bit(root_block,1);
	memset(buf, 0, 1024);
	i = nblocks-1;
	while (i < 8191)
	{
		set_bit(i,1);
		i++;
	}	
	put_block(3, buf);
	
  // WRITE YOUR OWN CODE
  //block number=0 means NO block ==> bmap does NOT include B0.
  //So, only the first (nblocks-1) bits are valid, the rest bits are invalid.

  //Block 1 to root_block# are already in USE ==> bmap should contain:
  //--------------------------------------------------------------
  //The first root_block# BITs        are USED        ==> set to 1
  //Bits root_block# to (nblocks-2)   are FREE        ==> clr to 0
  //Bits (nblocks-1) to 8191          are invalid     ==> set to 1
 //---------------------------------------------------------------
  //write buf[ ] to bmap block (3)
}

int make_imap()
{
	int i=0;
	set_bit(root_block,1);
	memset(buf, 0, 1024);
	i = 0;
	while (i < 10)
	{
		set_bit(buf,i);
		i++;
	}
	while (i < 1024)
	{
		clr_bit(buf,i);
		i++;
	}		
	put_block(4, buf);
  // WRITE YOUR OWN CODE
  //inode number=0 means NO inode => imap has exactly ninodes bits valid.
  //So, only the first ninodes bits are valid, the rest bits are invalid.
  
  //inodes 1 to 10 are reserved; (root_inode = #2).

  //The first 10 (0_th to 9_th) bits are USED     ==> set to 1
  //Bits 10 to (ninodes-1)           are FREE     ==> clr to 0
  //Bits ninodes to 8191             are invalid  ==> set to 1

  //write buf[ ] to imap block (4)
}


int make_super()
{
  printf("making super block ......\n");
  memset(buf, 0, 1024);
  sp = (struct ext2_super_block *)buf;

  sp->s_inodes_count = ninodes;                 /* Number of inodes     */
  sp->s_blocks_count = nblocks;                 /* Number of blocks     */
  sp->s_r_blocks_count = 0;                     /* No reserved blocks   */
  sp->s_free_blocks_count = free_blocks;	/* Free blocks count    */
  sp->s_free_inodes_count = free_inodes;	/* Free inodes count    */
  sp->s_first_data_block = 1;   	        /* First Data Block     */
  sp->s_log_block_size = 0;                     /* Block size 0=1K,2=4K */
  sp->s_log_frag_size  = 0;      	        /* Fragment size        */
  sp->s_blocks_per_group = 8192;	        /* Blocks per group     */
  sp->s_frags_per_group  = 8192;                /* Fragments per group  */
  sp->s_inodes_per_group = ninodes;	        /* Inodes per group     */
  sp->s_max_mnt_count = 20;     	        /* Maximal mount count  */
  sp->s_magic = 0xEF53;                         /* ext2 magic signature */  
  put_block(1, buf);
}


int make_group()
{
  printf("making group descriptors ......\n");
  memset(buf, 0, 1024);
  gp = (struct ext2_group_desc *)buf;

  gp->bg_block_bitmap = bmap;		   /* Blocks bitmap block */
  gp->bg_inode_bitmap = imap;		   /* Inodes bitmap block */
  gp->bg_inode_table  = inodes_start;	   /* Inodes table block */
  gp->bg_free_blocks_count = free_blocks;  /* Free blocks count */
  gp->bg_free_inodes_count = free_inodes;  /* Free inodes count */
  gp->bg_used_dirs_count = 1;   	   /* used directory count */
  put_block(2, buf);
}


int clear_inodes()  // write 0 to inode blocks
{
  int i; 
  memset(buf, 0, 1024);
  for (i=inodes_start; i<inodes_start+inodes_blocks; i++){
       put_block(i, buf);
  }
}


int make_root_inode()
{
  int i;
  printf("making root inode ......\n");
  memset(buf, 0, 1024);
  ip = (struct ext2_inode *)buf; 
  ip++;

  ip->i_mode = 0x41ED;		/* DIR and permissions  0100 000 111 101 101 */
  ip->i_uid  = 0;		/* Owner Uid */
  ip->i_size = 1024 ;		/* Size in bytes; has ONE data block */
  ip->i_gid =  0;		/* Group Id */
  ip->i_links_count = 2;	/* Links count = 2; for . and .. */

  ip->i_atime=ip->i_atime=ip->i_mtime = time(0L);  // time fields

  ip->i_blocks = 2;     	/* i_blocks count in 512-byte units */
  ip->i_block[0] = root_block;  /* 0_th data block number */

  for (i=1; i<15; i++)          // all other i_block[i] = 0
    ip->i_block[i] = 0;

  put_block(inodes_start, buf);
}


int make_root_block()
{ 
  printf("making root data block ......\n");
  memset(buf, 0, 1024);

  dp = (struct ext2_dir_entry_2 *)buf;   
  dp->inode = 2;		/* Inode number */
  strcpy(dp->name, ".");        /* File name */
  dp->name_len = 1;		/* Name length */
  dp->rec_len = 12;		/* Directory entry length */

  /*********************************************************************** 
    ext2 dir entries are variable length (min=12 bytes). Last entry's 
    rec_len must be set to the remaining length of the block. 
  ************************************************************************/
  cp = buf; 
  cp += dp->rec_len;            /* advance by rec_len */
  dp = (struct ext2_dir_entry_2 *)cp;
  dp->inode = 2;		/* Inode number */
  dp->name_len = 2;		/* Name length */
  strcpy(dp->name, "..");       /* File name */
  dp->rec_len = 1012;		/* Directory entry length */
  put_block(root_block, buf);
}



main(int argc, char *argv[])
{
  if (argc < 3){ // a.out /dev/fd0 nblocks [ninodes]
      printf("Usage a.out filename nblockk [ninodes]\n");
      exit(1);
  } 

  // open filename for RW
  fd = open(argv[1], O_WRONLY|O_TRUNC|O_CREAT);
  if (fd < 0){
      printf("open %s error\n", argv[1]); 
      exit(2);
  }

  nblocks = atoi(argv[2]);            /* number of blocks */
  if (nblocks > 1440){
     printf("too many blocks for %s\n", argv[1]);
     exit(1);
  }

  lseek(fd, (long)(BLK*(nblocks-1)), 0);   // seek to last block
  r = write(fd, buf, BLK);                 // write a block of 0
  if (r<0){
    printf("write to block %d failed\n", nblocks);
    exit(3);
  }
 
  ngroups = (nblocks + 8191)/8192;         /* number of groups       (1) */
  ngblocks= (ngroups*32 + BLK -1)/BLK; /* number of group blocks (1) */

  if (argc > 3)
    ninodes = atoi(argv[3]);
  else
    ninodes = nblocks/4;              /* default # of inodes */

  // ninodes should be a multiple of 8 so that every inode block is FULL.
  ninodes = 8*(ninodes/8);

  inodes_blocks = ninodes/8;          /* number of inodes blocks */

  bmap = 2 + ngblocks;                /* bamp block#          (3) */ 
  imap = bmap + 1;                    /* imap block#          (4) */
  inodes_start = imap + 1;            /* inodes start block#  (5) */

  root_block = inodes_start + inodes_blocks;   /* data block# of root */

  used_blocks = root_block + 1;       /* number of used blocks, including B0 */
  used_inodes = 10;                   /* inodes 1 to 10 are reserved */

  free_blocks = nblocks - used_blocks;        /* number of free blocks */
  free_inodes = ninodes - 10;                 /* number of free inodes */

  printf("\n************  mkfs on %s  *************\n", argv[1]);
  printf("nblocks      = %4d   ninodes     = %4d\n", nblocks, ninodes);
  printf("free_blocks  = %4d   free_inodes = %4d\n", free_blocks, free_inodes);
  printf("used_blocks  = %4d   used_inodes = %4d\n", used_blocks, used_inodes);
  printf("inodes_start = %4d   root_block  = %4d\n", inodes_start, root_block);
  printf("********************************************\n");

  /* make super block */
  make_super();

  /* make group table */
  make_group();

  printf("making blocks bit map ......\n");
  make_bmap();
int counter = 0,counter3=0;
  printf("making inode bit map ......\n");
  make_imap();
while(counter < 1024)
    {
        counter3 = 0;
        while(counter3 < 8)
        {
            if ( buf[counter] & (1 << counter3) )
            {
                printf("1");
            }
            else
            {   
                printf("0");
            }
            counter3++;
		}
  
        counter++;
    }
  close(fd);

  clear_inodes();
  make_root_inode();
  make_root_block();
	get_block(4,buf);
	//make_imap();
  // OPTIONAL : print the bitmaps as '0', '1'
	printf("Printing super block: ");
	counter = 0;counter3=0;
	get_block(4,buf);
	//while (counter < BLK*8)
	//{
	//	printf("%d", (((buf[counter/8]) & (1 << (i%8))) >> (i%8)));	
	//	counter++;
	//}	
	printf("\nANOTHER PRINTOUT LATER\n");
while(counter < 1024)
    {
        counter3 = 0;
        while(counter3 < 8)
        {
            if ( buf[counter] & (1 << counter3) )
            {
                printf("1");
            }
            else
            {   
                printf("0");
            }
            counter3++;
		}
  
        counter++;
    }
  close(fd);

  printf("**************  All Done  ******************\n");
}