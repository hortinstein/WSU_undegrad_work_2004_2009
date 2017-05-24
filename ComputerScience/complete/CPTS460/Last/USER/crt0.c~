
int argc;
char *argv[16];
#include "ucode.c"
token(cmd) char * cmd;
{
	int i;
	char* p;
	p=cmd;
	while(*p!='\0'){
		while (*p == ' '){			
			*(p++) = '\0';//zeroing out all spaces
		}
		if (*p != '\0'){
			argc++;//assigns the argument
			argv[argc] = p;
		}
		while (*p != ' ' && *p!='\0'){//forwards to the next spaces
			p++;		
		}
       		p++;
	}
		
}
 
int main0(s) char *s;
{
	token(s);
	main(argc, argv);
}



