/*******************************************************
*            main.c for LAB#1
*******************************************************/
//Daniel Rodgers
//Cpts 460

#include <string.h>
#define u8  unsigned char
#define u16 unsigned short
#define u32 unsigned long

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
};#define INODES_PER_BLOCK  (1024/sizeof(INODE))

struct ext2_dir_entry_2 {
	u32	inode;			/* Inode number */
	u16	rec_len;		/* Directory entry length */
	u8	name_len;		/* Name length */
	u8	file_type;
	char	name[255];      	/* File name */
};
typedef struct ext2_dir_entry_2 DIR;
typedef struct ext2_inode INODE;

char   buf1[1024], buf2[1024];

getBlock(blk, buf) u16 blk; char *buf;
{
	diskr((blk*2)/36,((blk*2)%36)/18,((blk*2)%36)%18, buf);
}
mygets(s) char *s;
{
	unsigned int i = 0;
	char x = getc();
	while(x != '\r')
	{
		putc(x);
		s[i] = x;
		i++;
		x = getc();
	}
	s[i] = '\0';
	putc('\n');
}

myprints(s) char *s;
{
	while(*s != '\0')
	{
		putc(*s);
		s++;
	}
}

u16 search(ip, name) struct ext2_inode *ip; char *name;
{
	char* cp;
	u16 i = 0;
	DIR *dp;
    if ((u16)ip->i_block[0] == 0)
    {
		return 0;
    }
    getBlock((u16)ip->i_block[0],buf1);
    cp = buf1;	
	dp = (DIR *)cp;
    while(cp < &buf1[1024])
    {
		i = 0;
		while( i < dp->name_len && dp->name[i] == name[i])
		{
			i++;
		}
		if( i == dp->name_len && dp->name[i-1] == name[i-1] )
			return dp->inode;
        cp += dp->rec_len;
        dp = (DIR *)cp;
    }
   	return(0);
}
INODE* getino(ino) u16 ino;
{
    getBlock((ino - 1)/(1024/sizeof(INODE)) + 5, buf1);
    return( (INODE*)buf1 + (ino - 1)%(1024/sizeof(INODE)) );
}
main()
{
	u16 i = 0;
	u32* indirect = 0;
	struct ext2_inode *ip;
	char bootname[10];
	setVideo();
	myprints("Welcome to Dan's extreme booter!\n\r");
	myprints("enter boot name: boot/");
	mygets(bootname);
	getBlock(5, buf1);
	ip = (struct ext2_inode *)buf1;
	ip++;
	i = search(ip, "boot");
	if( i == 0)
		return 1;
	ip =  getino(i);
	i = search(ip, bootname);
	if ( i == 0 )
		return 1;
	ip = getino(i);
	if ( i == 0 )
		return 1;
	getBlock((u16)ip->i_block[12],buf2);
	setes(0x1000);
	i = 0;

	while( i < 12)
	{
		putc('.');
		getBlock((u16)ip->i_block[i], (char*)0);
		inces();
		i++;
	}
	indirect = (u32*)buf2;
	while(indirect < &buf2[1024]) 
	{
		//putc('.');
		getBlock((u16)*indirect, (char*)0);
		indirect += 2;
		inces();
	}
	myprints("Done\n\r");
	return(0);
}
