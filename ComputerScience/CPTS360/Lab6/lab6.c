#include <fcntl.h>
#include <linux/ext2_fs.h>
#include <sys/types.h>
#include <stdio.h>
#define BLK 1024

typedef struct ext2_super_block SUPER;
typedef struct ext2_group_desc  GD;
typedef struct ext2_inode       INODE;
typedef struct ext2_dir_entry_2 DIR;

SUPER *sp;
GD    *gp;
INODE *ip;
DIR   *dp;

char rbuf[1024];
int fd, blk, i;

char buf[BLK], *cp;

int InodesBeginBlock;
int  fd, i, j, n, r;
int  nblocks, ninodes;
int BLOCK;
int  ngroups, ngblocks;
int  bmap, imap, inodes_start, inodes_blocks, root_block;

int  used_blocks, used_inodes;
int  free_blocks, free_inodes;

int super_print(int argc, char* argv[])
{
	
	fd = open(argv[1], O_RDONLY);
	lseek(fd,(BLK *  1), SEEK_SET);
	read(fd, buf, BLK);
	sp = (SUPER*)buf;

	printf("...***********Printing superblocks...***********\n");
	printf("...Total number of inodes on fs: %d\n",  sp->s_inodes_count);//unsigned long  s_inodes_count;
  	printf("...Total number of blocks on fs: %lo\n", sp->s_blocks_count );//unsigned long  s_blocks_count;
  	printf("...Total number of blocke reserved for super user: %lo\n", sp->s_r_blocks_count );//unsigned long  s_r_blocks_count;
  	printf("...Total number of free blocks on fs: %lo\n", sp->s_free_blocks_count );//unsigned long  s_free_blocks_count;
  	printf("...Total number of free inodes on fs: %lo\n", sp->s_free_inodes_count );//unsigned long  s_free_inodes_count;
  	printf("...The position on the fs of the first data block: %lo\n", sp->s_first_data_block );//unsigned long  s_first_data_block;
  	printf("...Logical block size in bytes: %lo\n", sp->s_log_block_size );//unsigned long  s_log_block_size;
  	printf("...Logical fragment size: %lo\n", sp->s_log_frag_size );//long           s_log_frag_size;
  	printf("...Total number of blocks %lo\n", sp->s_blocks_per_group );//unsigned long  s_blocks_per_group;
  	printf("...Total number of fragments contained in a group: %lo\n", sp->s_frags_per_group );//unsigned long  s_frags_per_group;
  	printf("...Total number of inodes in a group: %lo\n", sp->s_inodes_per_group );//unsigned long  s_inodes_per_group;
  	printf("...The time at which the last mount of FS was performed: %lo\n", sp->s_mtime );//unsigned long  s_mtime;
  	printf("...The time at whick the last write to the superblock was performed: %lo\n", sp->s_wtime );//unsigned long  s_wtime;
  	printf("...The number of time the fs has been mounted in read-write mode without having been checked: %lo\n", sp->s_mnt_count );//unsigned short s_mnt_count;
  	//printf("%lo",  )//short          s_max_mnt_count;
  	printf("...The smagic number that identifies file system...should be 0xEF53 : %x\n",  sp->s_magic);//unsigned short s_magic;
  	//printf("%lo",  )//unsigned short s_state;
  	//printf("%lo",  )//unsigned short s_errors;
  	//printf("%lo",  )//unsigned short s_pad;
  	//printf("%lo",  )//unsigned long  s_lastcheck;
  	//printf("%lo",  )//unsigned long  s_checkinterval;
  	//printf("%lo",  )//unsigned long  s_reserved[238];
	close(fd);
}
int group_print (int argc, char* argv[])
{
	fd = open(argv[1], O_RDONLY);
	lseek(fd,(BLK *  2), SEEK_SET);
	read(fd, buf, BLK);
	gp = (GD*)buf;
	printf("...***********Printing groupblock...***********\n");
	printf("...Points to the blocks bitmap block for the group: %d\n",  gp->bg_block_bitmap);//unsigned long  bg_block_bitmap;
  	printf("...Points to the inodes bitmap block for the group: %d\n",  gp->bg_inode_bitmap);//unsigned long  bg_inode_bitmap;
  	printf("...Points to the inodes table first block: %d\n",  gp->bg_inode_table);//unsigned long  bg_inode_table;
  	printf("...Number of free blocks in the group: %d\n",  gp->bg_free_blocks_count);//unsigned short bg_free_blocks_count;
  	printf("...Number of free inodes in the group: %d\n",  gp->bg_free_inodes_count);//unsigned short bg_free_inodes_count;
  	printf("...Number of inodes allocated to directories in the group: %d\n",  gp->bg_used_dirs_count);//unsigned short bg_used_dirs_count;
  	printf("...Padding: %d\n",  gp->bg_pad);//unsigned short bg_pad;

	InodesBeginBlock = gp->bg_inode_table;

	


	
	close(fd);
}
int root_inode_find (int argc, char* argv[])
{
	fd = open(argv[1], O_RDONLY);
	lseek(fd,(BLK *  InodesBeginBlock), SEEK_SET);
	read(fd, buf, BLK);
	ip = (struct ext2_inode*)buf +1;
	
	printf("...***********Printing / inode...***********\n");
	printf("...The inode mode: %x\n",  ip->i_mode);//unsigned long  bg_block_bitmap;
  	printf("...The file size in bytes: %d\n",  ip->i_size);//unsigned long  bg_inode_bitmap;
  	

	InodesBeginBlock = gp->bg_inode_table;
}
int main (int argc, char* argv[])
{
	printf("%s",argv[1]);		
	super_print(argc,argv);
	group_print(argc,argv);
	root_inode_find(argc,argv);
}
