#include "ucode.c"
#include "io.c"
int bp;
int bn;
int new_count = 0;
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
int has_pattern(bp, bn, pat, buffer)int bp; int bn; char* pat; char* buffer;
{
	int i = bp;
	int i2 = 0;
	while(i != bn)
	{
		if(buffer[i] == pat[0])
		{
			i2 = 0;
			while(1)
			{
				if( i >= bn)
					return 0;
				if(pat[i2] == '\0')
					return 1;
				if(pat[i2] != buffer[i])
					break;
				i2++;
				i++;
			}
		}
		i++;
	}
	return 0;
}
void print_to(start, finish, buffer)int start; int finish; char*buffer;
{
	char buf2[256];
	int i = 0;
	while(start <= finish)
	{
		buf2[i] = buffer[start];
		i++;
		start++;
	}
	buf2[i] = '\0';
	myprintf("%d: %s\n",new_count, buf2);
}
void waitin(n)int n;
{
	char x;
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
	}
}
main(argc, argv) int argc; char *argv[];
{
	int file;
	int done = 0;
	char buff[256];
	bp = 0;
	bn = 0;
 	myprintf("////////////////////////////////////////////\n\r");
	myprintf("Dan's grep\n\r");
 	myprintf("////////////////////////////////////////////\n\r");
	if( argc > 2)
	{
		file = open(argv[2], O_RDONLY);
	}
	else
	{
		file = 0;
	}
	read(file, buff, 256);
	while(1)
	{
		bp = bn;
		bn = newline(bp,buff);
		new_count++;
		if(has_pattern(bp,bn,argv[1],buff))		
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
}
