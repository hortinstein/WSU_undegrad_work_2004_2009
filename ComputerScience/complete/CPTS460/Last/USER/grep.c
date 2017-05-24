////////////////////////////////////////////////////////////////////////////////////////
//cat.c
//
//This is the file where I implemented grep for the project
//
////////////////////////////////////////////////////////////////////////////////////////
#include "ucode.c"

int findmepattern(pattern,line)char *pattern;char *line;
{
	char *p,*lp;
	int i=0,pi,ti;
	p = pattern;
	lp = line;
	while (lp[i] != '\0'){
		ti = i;
		pi = 0;		
		while (lp[ti] == p[pi]){
			ti++;
			pi++;
			if (p[pi] == '\0')
				return 1;		
		}
		//printf("%c",lp[i]);
		i++;
	}
	return 0;
}

main(argc, argv) int argc; char *argv[];   // invoked by exec("cat somefile")
{
	int file,i=0;	
	char buffer[128];
	char templine[128];	
	char gettingc;
	int tempfile;
	
	//check if argv1 is there if not open stdin....

	printf("%d\n\n",argc);
	if (argc >2){
		file = open(argv[argc-1], O_RDONLY);
	}
	else{	
		file = 0;//opens std in because this is most likely a redirected command
	}

	
	while (1 == read (file,buffer,1) )
	{
		//printf("%c",buffer[0]);
		if (buffer[0] == '\n')
		{
			templine[i] = '\0';			
			if (findmepattern(argv[1],templine) ==1)
			{
				printf("%s",templine);			
				putc('\n');			
			}		
			i =0;		
		}		
		else
		{
			templine[i] = buffer[0];
			i++;			
		}	
	}
	return;

}

