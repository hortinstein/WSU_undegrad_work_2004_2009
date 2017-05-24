#include "ucode.c"
#include "io.c"

main(argc, argv) int argc; char *argv[];
{
	char buff[256];
	char file1[32];
	char file2[32];
	int i = 0;
	int i2 = 0;
	int dest;
	int sorc;
	myprintf("//////////////////////////////////////////// \n");
	myprintf("DASH: Welcome to dans cp (file copy only!) \n");
	myprintf("//////////////////////////////////////////// \n");
	//myprintf("%s\n%s\n%s\n",argv[0],argv[1],argv[2]);
	//mygets(buff);
	sorc = open(argv[1], O_RDONLY);
	dest = open(argv[2], O_WRONLY|O_CREAT);
	while(read(sorc,buff, 256))
	{
		i = 0;
		while(buff[i] != '\0' && i < 256)
		{
			i++;
		}		
		write(dest,buff,i);
	}
}
