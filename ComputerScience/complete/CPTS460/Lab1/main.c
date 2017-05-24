//Alex Hortin
//Cpts460
//Lab1
//Write a booter
//Notes:
//#include <string.h>

#define u8  unsigned char
#define u16 unsigned short
#define u32 unsigned long
#define BLOCK_SIZE 1024
#define INODE_BLK_START 5

typedef struct ext2_inode {
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
    u32 dummy;
	u32	i_block[15];    /* Pointers to blocks */
    u32 pad[7];         /* inode size MUST be 128 bytes */
} INODE;

typedef struct ext2_dir_entry_2 {
	u32	inode;			/* Inode number */
	u16	rec_len;		/* Directory entry length */
	u8 	name_len;		/* Name length */
	u8	file_type;
	char	name[255];      	/* File name */
} DIR;

/*  
	included functions 
	char getc();
   	void putc(char c);
   	void diskr(int cyl, int head, int sector, char *buf)
   	void setes(int segment);
   	void inces();

helpfull hints 
-typecasting is your friend compat and filesize 
-look at the inode and directory entry data structures...you need them
-pointer arithmatic can help you 
-dont create and use unnessecary variables
-adding any library function can greatly increase size
-directory entry name strings are not null terminated
-set the ES register only after youve read into the buffer
-pay attention in notes for when buf = 0
-http://www.eecs.wsu.edu/~cs360/sp08 old 360 notes
-at the bottom of lab 1 diagram of disk head cylinder sectors....need that for getblk
-mailman's algorithm
-aim name : defiantx19
*/



///////////////////////////////////////////////////////////////////////////////////
//		Global vars
#define BLK 1024
#define INODEBLK 5
char buffer[BLK];
char buffer1[BLK];
INODE *ip; 
DIR *dp;
char name[10];
unsigned long* ind = 0;	
//
//
///////////////////////////////////////////////////////////////////////////////////

//simple print string function
void prints(s) char *s;
{
	unsigned short i = 0;
	
	while (s[i] != '\0'){
		putc(s[i]);
		i++;
	}
}
//takes input from the command line to 
void gets(s) char *s;
{
	unsigned short i = 0;
	char t = '\0';	
	while (t != '\r'){
		t = getc();
		putc(t);
		s[i] = t;		
		i++;
	}
	
}

int  get_block(blk, buf)  u16 blk; char *buf;
{
	///////////////////////////////////////////////////////////////////////////////////
	//             (1). Compute cyl, head, sector from blk;
	//                 NOTE: cyl, head, sector are all counted from 0.
    // 					diskr(cyl, head, sector, buf);
	///////////////////////////////////////////////////////////////////////////////////
    diskr((blk*2)/36,((blk*2)%36)/18,((blk*2)%36)%18, buf);    
	///////////////////////////////////////////////////////////////////////////////////
	//         (3). return SUCCESS or FAIL;
	///////////////////////////////////////////////////////////////////////////////////

}
//searches the inodes for a user given name
int search(name) char *name;
{
	unsigned short i = 0;
	char *cp = buffer;
	dp = (DIR *)cp;
	
    while(cp < &buffer[1024])
    {
		while( i < dp->name_len && dp->name[i] == name[i])
		{
			i++;//increments through the name
		}
		if( i == dp->name_len && dp->name[i-1] == name[i-1] ){//checks to see that the length and the final letter of the name match up
			putc('\0');			
			prints(dp->name);//debugging to print names out of current directories
			return dp->inode;//returns the i node for the directory
		}
        cp += dp->rec_len;//adds the directory length so CP can search the next one
        dp = (DIR *)cp;//casts dp to the new location
    }
	return(0);
}
int main()
{
	
	unsigned short i =0;

	///////////////////////////////////////////////////////////////////////////////////
	//     (1). Prompt for filename to boot, e.g. mtx or image, etc. You may assume
	//          that all bootable files are in the /boot directory.
	///////////////////////////////////////////////////////////////////////////////////
	prints("boot: ");
	gets(name); //user should input MTX
	//putc('\n');
	///////////////////////////////////////////////////////////////////////////////////
	//     (2). Find the file. Recall that "finding a file amounts to finding its 
	//          inode". 
	/////////////////////////////////////////////////////////////////////////////
	get_block(INODE_BLK_START, buffer);//loads the block with the inodes
	ip = (INODE *) buffer;
	ip++; //inc since the second inode is where root is located
	get_block((unsigned short) ip->i_block[0],buffer);	
	i = search("boot");//searches for the boot directory in 
	if (i != 0){
 		get_block((i-1)/(BLOCK_SIZE/sizeof(INODE))+INODE_BLK_START, buffer);//n_blk = (ino - 1)/INODES_PER_BLOCK + inode_start; from 360
    	ip = ( (INODE*)buffer + (i - 1)%(BLOCK_SIZE/sizeof(INODE)) );//i_num = (ino - 1)%INODES_PER_BLOCK; from 360
	    get_block((unsigned short) ip->i_block[0],buffer);
		i = search(name);//searches for the boot directory in 	
		if (i != 0){		
			get_block((i-1)/(BLOCK_SIZE/sizeof(INODE))+INODE_BLK_START, buffer);//n_blk = (ino - 1)/INODES_PER_BLOCK + inode_start; from 360
    		ip = ( (INODE*)buffer + (i - 1)%(BLOCK_SIZE/sizeof(INODE)) );//i_num = (ino - 1)%INODES_PER_BLOCK; from 360
	    
		}		
	}
	///////////////////////////////////////////////////////////////////////////////////
	//    	int n_blk = 0;
    //		int i_num = 0;
    //		n_blk = (ino - 1)/INODES_PER_BLOCK + inode_start;
    //		i_num = (ino - 1)%INODES_PER_BLOCK;
    //		get_block(device, rbuf, n_blk);
    //		return( (INODE*)rbuf + i_num );	
	///////////////////////////////////////////////////////////////////////////////////
	//     (3). From the file's inode, find the disk blocks of the file:
	//               i_block[0] to i_block[11] are DIRECT blocks, and
	//               i_blokc[12] points to INDIRECT blocks.
	//          MTX kerenl has at most 64 (1KB) blocks, so no double-indirect blocks.
	///////////////////////////////////////////////////////////////////////////////////
	get_block((u16)ip->i_block[12],buffer1);//getting the indirect blk	
	setes(0x1000);//the segment that bs.s tries to boot from
	i = 0;
	while( i < 12)
	{
		get_block((u16)ip->i_block[i],(char *) 0);//loading the direct blocks into memory
		inces();//incrementing the es reg
		i++;
	}
	
	ind = (u32*)buffer1;
	
	while(*ind) 
	{
		putc('.');
		//gets(name);//debugging ishniz
		get_block((u16)*ind, (char *)0);//loading the indirect blocks
		ind += 1;		
		inces();//incrementing the es reg
	}

	///////////////////////////////////////////////////////////////////////////////////
	//     (4). Load the blocks of /boot/mtx into memory at the segment 0x1000.
	///////////////////////////////////////////////////////////////////////////////////



	///////////////////////////////////////////////////////////////////////////////////
	//     (5). return 0 to bs.s for OK, return non-zero for failure.
	///////////////////////////////////////////////////////////////////////////////////



	///////////////////////////////////////////////////////////////////////////////////
	//     ==========================================================================  
	//     (6). If YOUR main() loads the disk blocks of mtx successfully and returns 0, 
	//          bs.s will jump to (0x1000, 0) to start up MTX.
	///////////////////////////////////////////////////////////////////////////////////


	

	///////////////////////////////////////////////////////////////////////////////////
	//prelab
	//		/*prints("What's your name?");
	//		gets(name);
	//		prints("welcome, ");
	//		prints(name);
	//		if (name[0] == '\r'){
	//			prints("byebye");
	//		}	
	//		gets(name);*/
	///////////////////////////////////////////////////////////////////////////////////
	
	return(0);		
}


