#include <string.h>
#define u8  unsigned char
#define u16 unsigned short
#define u32 unsigned long
#define inode_start 5
#define BLOCK_SIZE 1024
struct ext2_inode {
	u16	i_mode;		/* File mode */
	u16	i_uid;		/* Owner Uid */
	u32	i_size;		/* Size in bytes */
	u32	i_atime;	/* Access time */
	u32	i_ctime;	/* Creation time */
	u32	i_mtime;	/* Modification time */
	u32	i_dtime;	/* Deletion Time */
	u16	i_gid;		/* Group Id */
	u16	i_links_count;	/* Links count */
	u32	i_blocks;	/* Blocks count */
	u32	i_flags;	/* File flags */
        u32     dummy;
	u32	i_block[15];    /* Pointers to blocks */
        u32     kcpad[7];       /* pad to 32 long or 128 bytes */    
};
struct header{
  long sep;
  long gap;
  long tsize;
  long dsize;
  long bsize;
  long zero;
  long tot;
  long ssize;
} *hp;

struct ext2_dir_entry_2 {
	u32	inode;			/* Inode number */
	u16	rec_len;		/* Directory entry length */
	u8	name_len;		/* Name length */
	u8	file_type;
	char	name[255];      	/* File name */
};
typedef struct ext2_dir_entry_2 DIR;
typedef struct ext2_inode INODE;
#define INODES_PER_BLOCK  (1024/sizeof(INODE))
char* path[20];
char buf1[1024];
char buf2[1024];
INODE* ip;
DIR* dp;
get_block(blk, buf) u16 blk; char *buf;
{
	diskr((blk*2)/36,((blk*2)%36)/18,((blk*2)%36)%18, buf);
}
INODE* getInode(ino)int ino;
{
    int n_blk = 0;
    int i_num = 0;
    n_blk = (ino - 1)/INODES_PER_BLOCK + inode_start;
    i_num = (ino - 1)%INODES_PER_BLOCK;
    get_block(n_blk,buf1);
    return( (INODE*)buf1 + i_num );
}
token_path(pathname)char* pathname;
{
    char* tp;
    int counter = 0;
	while( counter < 20)
	{
		path[counter] = "";
		counter++;
	}
	counter = 0;
    tp = strtok(pathname, "/"); 
    while( tp != NULL)
    {
        path[counter] = tp;
        counter++;
        tp = strtok(NULL, "/");
    }
    path[counter] = NULL;
}
u16 inode_helper(pathname)char *pathname;
{
    int i;
    char* cp;
    int num = 0;
    int blk;
    char* temp[256];
    
    for (i = 0; i < 12; i++)
    {
        blk = ip->i_block[i];
        if (blk==0)
        {
            break;
        }
        get_block(blk,buf1);
    
        dp = (DIR *)buf1;
        cp = buf1;
        while(cp < &buf1[BLOCK_SIZE])
        {
            bzero(temp, 256);
            strncpy((char*)temp, dp->name, dp->name_len);
            if( 0 == strcmp((char*)temp, pathname) )
            {
                num = dp->inode;
            }
            cp += dp->rec_len;
            dp = (DIR *)cp;
        }
    }
    return(num);
}
u16 getino(pathname)char* pathname;
{
    int counter;
    int i_num = 0;
    int i_num2 = 0;
    int n_blk = 0;
    if(0 == strcmp(pathname, "/") )
	{
        path[0] = ".";
		path[1] = "";
	}
	else
	{
    	token_path(pathname);
	}

    get_block(inode_start, buf1);
    ip = (INODE*)buf1+1;


    for(counter = 0;  path[counter] != NULL ; counter++)
    {

        i_num = inode_helper(path[counter]);

        if(i_num != 0)
        {
            n_blk = (i_num - 1)/INODES_PER_BLOCK + inode_start;
            i_num2 = (i_num - 1)%INODES_PER_BLOCK;
            get_block(n_blk, buf1);
            ip = (INODE*)buf1+i_num2;
        }
        else
        {
            break;
        }
    }
    return(i_num);
}
