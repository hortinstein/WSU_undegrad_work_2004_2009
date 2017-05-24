//Alex Hortin
//Cpts460
//Lab2 - Prelab myio.c
//
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//	(1). Write YOUR own printf() as speicified in the class lecture.
//     	Use your printf() in an io.c file to generate the MTX kernel.
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
char *seq = "0123456789ABCDEF";

print_int(inInt) int inInt;
{
	if (inInt == 0)
	{
		putc('0');
	}
	if (inInt < 0)
	{
		putc('-');
		inInt = -1 * inInt;
	}
	while (inInt > 0)
	{
		putc(seq[inInt%10]);
		 inInt/=10;
	}	
}
print_hex(inHex) int inHex;
{
	if (inHex == 0)
	{
		putc('0');
	}
	if (inHex < 0)
	{
		putc('-');
		inHex = -1 * inHex;
	}
	while (inHex > 0)
	{
		putc(seq[inHex%16]);
		 inHex/=16;
	}	
}
void prints(s) char *s;
{
	unsigned short i = 0;
	
	while (s[i] != '\0'){
		putc(s[i]);
		i++;
	}
}
	
printf(inString) char* inString;
{
	int *varList = &inString;
	int i=0;	
	varList++;	
	while (inString[i] != '\0')//checks for the null termination string meaning the end of input
	{
		if (inString[i] == '%')
		{
			if (inString[i+1] == 'd')
			{
				print_int(*varList);
				varList++;				
			}
			if (inString[i+1] == 'c')
			{
				putc((char)*varList);
				varList++;	
			}
			if (inString[i+1] == 's')
			{
			prints((char *)*varList);
				varList++;
			}
			i+=2;
		}
	
		else//just a basic string
		{
			putc(inString[i]);
			if (inString[i] == '\n')
				putc('\r');		
			i++;
				
		}
	
	}
	
}
void gets(s) char *s;
{
	unsigned short i = 0;
	char t = '\0';	
	while (t != '\r'){
		t = getc();
		putc(t);
		s[i] = t;		
		i++;
	}
}

