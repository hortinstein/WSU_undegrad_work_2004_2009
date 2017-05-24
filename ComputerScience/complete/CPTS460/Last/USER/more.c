////////////////////////////////////////////////////////////////////////////////////////
//cat.c
//
//This is the file where I implemented cat for the project
//
////////////////////////////////////////////////////////////////////////////////////////
#include "ucode.c"

int waitme(){
	char buf[20];
	int in;
	//printf("-------------MORE----------\n");
	in = open("/dev/tty0", O_RDONLY);//opens std in because this is most likely a redirected command
	gets(buf);
	while(1)//busy wait...better way to do this?
	{
		read(in, buf, 1);
		if( buf[0] == ' ')//returns zero because it wants to reprint lines
			return 0;
		if (buf[0] == 'q')
		{
			putc('\n');
			exit(1);
		}
		if( buf[0] == '\r')///need to ask what the problem is here
			return 27;//supposed to print 1 line
	}
}

main(argc, argv) int argc; char *argv[];   // invoked by exec("cat somefile")
{
	int file,row = 0,column=0;	
	char buffer[128];
	char gettingc;
	int tempfile;
	printf("...HORTINsMORE\n");
	//check if argv1 is there if not open stdin....
	if (argc > 1)	
		file = open(argv[1], O_RDONLY);
	else
		file = 0;	
		
	while (1 == read (file,buffer,1) )
	{
		printf("%c",buffer[0]);
		if (buffer[0] == '\n')
			row++;			
		if (row >= 25)
			row=waitme();				
	}
	return;
}

