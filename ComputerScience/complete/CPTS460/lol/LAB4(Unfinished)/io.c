#include <stdarg.h>
#include <string.h>
unsigned short pow(x,y)unsigned short x;unsigned short y;
{
	int t = x;
	if( y == 0)
		return 1;
	while(y > 1)
	{
		t = t * x;
		y--;
	}
	return t;
}
print_hex(x,hexpower)int x; short hexpower;
{
	while(x >= 0 && hexpower >= 0)	
	{
		if( x >= (15 * pow(16, hexpower)) )
		{
			x = x - 15*pow(16, hexpower);
			putc('F');
		}
		else if( x >= 14*pow(16, hexpower) )
		{
			x = x - 14*pow(16, hexpower);
			putc('E');
		}
		else if( x >= 13*pow(16, hexpower) )
		{
			x = x - 13*pow(16, hexpower);
			putc('D');
		}
		else if( x >= 12*pow(16, hexpower) )
		{
			x = x - 12*pow(16, hexpower);
			putc('C');
		}
		else if( x >= 11*pow(16, hexpower) )
		{
			x = x - 11*pow(16, hexpower);
			putc('B');
		}
		else if( x >= 10*pow(16, hexpower) )
		{
			x = x - 10*pow(16, hexpower);
			putc('A');
		}
		else if( x >=  9*pow(16, hexpower) )
		{
			x = x -  9*pow(16, hexpower);
			putc('9');
		}
		else if( x >=  8*pow(16, hexpower) )
		{
			x = x -  8*pow(16, hexpower);
			putc('8');
		}
		else if( x >=  7*pow(16, hexpower) )
		{
			x = x -  7*pow(16, hexpower);
			putc('7');
		}
		else if( x >=  6*pow(16, hexpower) )
		{
			x = x -  6*pow(16, hexpower);
			putc('6');
		}
		else if( x >=  5*pow(16, hexpower) )
		{
			x = x -  5*pow(16, hexpower);
			putc('5');
		}
		else if( x >=  4*pow(16, hexpower) )
		{
			x = x -  4*pow(16, hexpower);
			putc('4');
		}
		else if( x >=  3*pow(16, hexpower) )
		{
			x = x -  3*pow(16, hexpower);
			putc('3');
		}
		else if( x >=  2*pow(16, hexpower) )
		{
			x = x -  2*pow(16, hexpower);
			putc('2');
		}
		else if( x >=  1*pow(16, hexpower) )
		{
			x = x -  1*pow(16, hexpower);
			putc('1');
		}
		else 
		{
			putc('0');
		}
		hexpower--;
	}
}
print_int(x) int x;
{
	int p = 10;
	int num;
	int temp;
	num = x / 10;		
	for(num = x /10; num > 0; p = p * 10)
	{
		num = num/10;
	}
	p = p / 10;
	num = x;
	while( p > 0)
	{
		temp = num / p;
		if (temp == 0)
			putc('0');
		if (temp == 1)
			putc('1');
		if (temp == 2)
			putc('2');
		if (temp == 3)
			putc('3');
		if (temp == 4)
			putc('4');
		if (temp == 5)
			putc('5');
		if (temp == 6)
			putc('6');
		if (temp == 7)
			putc('7');
		if (temp == 8)
			putc('8');
		if (temp == 9)
			putc('9');
		num = num - temp*p;		
		p = p/10;
	}	
}
prints(fmt) char* fmt;
{
	char str_temp[100];
	unsigned short i2 = 0;
	unsigned short x = 0; 
	unsigned short i = 0;
	va_list ap;
	va_start(ap, fmt);
	while (fmt[i] != '\0')
	{
		if( fmt[i] == '%' )
		{
			i++;
			if(fmt[i] == 'd')
			{
				x = va_arg(ap, int);
				print_int(x);
				i++;			
			}
			else if (fmt[i] == 'c')
			{
				putc(va_arg(ap, char));
				i++;
			}
			else if (fmt[i] == 'l')
			{
				x = va_arg(ap, long);
				print_hex(x,6);
				i++;			
			}
			else if (fmt[i] == 'x')
			{
				x = va_arg(ap, int);
				print_hex(x,3);
				i++;			
			}
/*			else if (fmt[i] == 's')
			{
				x = va_arg(ap, short);
				print_hex(x,1);
				i++;			
			}*/
			else if (fmt[i] == 's')
			{
				i2 = 0;
				strcpy(str_temp,va_arg(ap, char*));
				while ( str_temp[i2] != '\0')
				{
					putc(str_temp[i2]);
					i2++;
				}
				i++;
			}
		}
		else
		{
			putc(fmt[i]);
			if(fmt[i] ==  '\n')
				putc('\r');
			i++;
		}
	}
	va_end(ap);
}
mygets(s) char *s;
{
	unsigned short i = 0;
	char x = getc();
	while(x != '\r')
	{
		putc(x);
		s[i] = x;
		i++;
		x = getc();
	}
	s[i] = '\0';
	putc('\n');
	putc('\r');
}
