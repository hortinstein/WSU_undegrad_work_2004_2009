////////////////////////////////////////////////////////////////////////////////////////
//cat.c
//
//This is the file where I implemented cat for the project
//
////////////////////////////////////////////////////////////////////////////////////////
#include "ucode.c"

main(argc, argv) int argc; char *argv[];   // invoked by exec("cat somefile")
{
	int file;	
	char buffer[128];
	printf("%d\n\n",argc);
	if (argc >= 2){
		file = open(argv[1], O_RDONLY);
			
		while (1 == read (file,buffer,1) )
		{
			printf("%c",buffer[0]);
		}
	}
	else{	
		file = 0;//opens std in because this is most likely a redirected command
		while (1 == read (file,buffer,1)){
			gets(buffer);
			printf("%s\n",buffer);		
		}
	}
}

