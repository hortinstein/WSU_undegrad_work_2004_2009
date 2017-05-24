#include "ucode.c"
#include "io.c"
int bp;
int bn;
int newline(start, buffer) int start; char* buffer;
{
	int i = start+1;
	while(buffer[i] != '\0')
	{
		if(buffer[i] == '\n' || buffer[i] == '\r')
			return i;
		i++;
	}
	return i;
}
void print_to(start, finish, buffer)int start; int finish; char*buffer;
{
	while(start != finish)
	{
		putc(buffer[start]);
		start++;
	}
}
void waitin(n)int n;
{
	char buff[256];
	char x;
	int stdin;
	stdin = open("/dev/tty0", O_RDONLY);
	myprintf("%d", stdin);
	mygets(buff);
	while(1)
	{
		read(stdin, buff, 1);
		if( buff[0] == ' ')
			break;
		if (buff[0] == 'q')
		{
			putc('\n');
			exit(1);
		}
	}
/*
	while(1)
	{
		x = getc();
		if( x == ' ')
			break;
		if (x == 'q')
		{
			putc('\n');
			exit(1);
		}
	}*/
}
main(argc, argv) int argc; char *argv[];
{
	int file;
	int new_count = 0;
	int done = 0;
	int char_count = 0;
	char buff[256];
	bp = 0;
	bn = 0;
 	myprintf("////////////////////////////////////////////\n");
	myprintf(" Dan's more (more or less)\n");
 	myprintf("////////////////////////////////////////////\n");
	/*myprintf("argv[0] %s\n",argv[0]);
	myprintf("argv[1] %s\n",argv[1]);
	myprintf("argv[2] %s\n",argv[2]);
	mygets(buff);*/
	if( argc > 1)
	{
		file = open(argv[1], O_RDONLY);
	}
	else
	{
		file = 0;
	}
		if(!read(file, buff, 256))
			return 1;
		while(1)
		{
			//0 = read(file, buff, 256)
			bp = bn;
			bn = newline(bp,buff);
			//myprintf("bp = %d\n",bp);
			//myprintf("bn = %d\n",bn);
			char_count = char_count + bn - bn;

			if(buff[bn] != '\0')
				new_count++;
			else
			{
				while(char_count >= 80)
				{
					char_count = char_count - 80;
					new_count++;
				}
			}
			if(new_count >= 29)
			{
				waitin(0);
				new_count = 0;
				char_count = 0;
			}
			print_to(bp,bn,buff);
			if(done)
				break;
			if(buff[bp] == '\0')
			{
				if(!read(file, buff, 256))
					done = 1;
				bp = 0;
				bn = 0;
			}
			
		}
	putc('\n');
	putc('\r');
	while(1){}
}
