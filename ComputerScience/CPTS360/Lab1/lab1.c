///////////////////////////////////////////////////////////////////////////////
/// \author       Alex Hortin
/// \date         8/27/07
/// \brief        This is the first lab of CS360
///
/// I am creating a program that uses Partition table, fdisk, structures in C, 
/// read/write special files, using c and the linux terminal
///
/// REVISION HISTORY:
///
/// NONE
///            
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
//
#include <stdio.h>
#include <fcntl.h>


// LOCAL INCLUDES
//

//This structure is the place where the memory from the buffer will be placed

struct partition 
{
	unsigned char drive;		/* 0x80 - active */

	unsigned char head;		/* starting head */
	unsigned char sector;		/* starting sector */
	unsigned char cylinder;		/* starting cylinder */

	unsigned char sys_type;		/* partition type */

	unsigned char end_head;		/* end head */
	unsigned char end_sector;	/* end sector */
	unsigned char end_cylinder;	/* end cylinder */

	unsigned long start_sector;	/* starting sector counting from 0 */
	unsigned long nr_sectors;       /* nr of sectors in partition */
};

struct partition* print_partition(struct partition *p);

int main (int argc, char *argv[])
{
	//Local Variables
    char buf[512];
    int fd = 0; 
    int r = 0;
	int i=0, i2 = 0;
	int sector = 0;
    struct partition* p;
	struct partition* ext_temp;
	unsigned char ext_end_cylinder;
	unsigned long temp_start_sector;


    //Checking to make sure that there is a disk provided
    if (argc < 2) 
    {
        printf("\n\nPlease provide a path for the disk to open\n\n");
        return;
    }
    
    printf("Opening %s\n", argv[1]);

    fd = open(argv[1], O_RDONLY);          // open the command line argumen for READ
    
	r = read(fd, buf, 512);                // read 512 bytes into buf

    printf("%d bytes read from Master Boot Record\n", r);// show result
    p = (struct partition *) &buf[446];//assigns the struct to the part of the mbr containing the partition table
    printf("System type:    		  Start:    End:    Number of Blocks:    \n");
	for(i = 0; i < 4; i++)
    {
			
		if(p->sys_type == 5) //This goes to a special handle procedure for extended types
	    {
			ext_end_cylinder = (p->end_cylinder); 
			temp_start_sector = (p->start_sector);

			print_partition(p);	// this prints and incriments the partition in struct p
	        lseek(fd, p->start_sector*512, 0);
	        r = read(fd, buf, 512);
			p = ext_temp = (struct partition*) &buf[446];
			print_partition(p);	// this prints and incriments the partition in struct p
			p++;	
			//while (p->end_cylinder != ext_end_cylinder)
			for( i2 = 0; i2 < 3; i2++)			
			{							
				lseek(fd, (p->nr_sectors + temp_start_sector)*512,0);
        		r = read(fd, buf, 521);  
        		p = (struct partition*) &buf[0x1BE];	
				print_partition(p);	// this prints and incriments the partition in struct p
		
			}
					
		} 
		else
		{
			p = print_partition(p);	// this prints and incriments the partition in struct p
			p++;
		}
	}
    close(fd);                             // close opened file

}

struct partition* print_partition(struct partition *p)
{
		int i=0;
		if((p->sys_type) == 6) 
		{
			printf("FAT16                ");//if else block to show different OS-Types
		}
    	else if ((p->sys_type) == 131)
		{      		
			printf("Linux                ");//if else block to show different OS-Types
      	}
		else if ((p->sys_type) == 130)
		{ 
      		printf("Linux swap / Solaris ");//if else block to show different OS-Types
      	}
      	else if ((p->sys_type) == 0xC || (p->sys_type) == 0xc)
		{ 	
      		printf("W95 FAT32 (LBA)      ");//if else block to show different OS-Types
		}
		else if ((p->sys_type) == 5)
		{ 
      		printf("Extended             ");//if else block to show different OS-Types
		}
		else if ((p->sys_type) == 129)
		{  
      		printf("Minix / old Linux    ");//if else block to show different OS-Types
		}
		else if ((p->sys_type) == 0xb)
		{ 
      		printf("W95 FAT32            ");//if else block to show different OS-Types
		}
		else
		{		      		
			printf("Uknown               ");//if else block to show different OS-Types
   		}	
		printf("%4x          %4d    %4d       %4lu\n", (p->sys_type), (p->cylinder + 1), (p->end_cylinder + 1), ((p->nr_sectors)/2));
		
		
		
		return (p);   
	}
