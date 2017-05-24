#include "ucode.c"
#include "io.c"

main(argc, argv) int argc; char *argv[];
{
	int file;
	char buff[256];
 	/*;*/

	if( argc > 1)
	{
		myprintf("////////////////////////////////////////////\n");
		myprintf(" Dan's not quite as kool as kacy's cat\n");
		myprintf("    (`. \n");
   		myprintf("     ) ) \n");
    	myprintf("    ( ( \n");
    	myprintf("     \\ \\            .----. \n");
    	myprintf("      \\ \\          ( MEOW!) \n");
    	myprintf("    .-'  `-.        `.  .-` \n");
    	myprintf("   /        `.        \\/ \n");
    	myprintf("  (      )    `-._ ,    _ \n");
    	myprintf("   )   ,'         (.\\--'( \n");
    	myprintf("   \\  (         ) /      \\ \n");
    	myprintf("    \\  \\_(     / (    <6 (6 \n");
    	myprintf("     \\_)))\\   (   `._  .:Y)- \n");
    	myprintf("      '''  \\   `-._.'`---^_))) \n");
    	myprintf("            `-._ )))       ``` \n");
    	myprintf("                 ``` \n");
 		myprintf("////////////////////////////////////////////\n");
		file = open(argv[1], O_RDONLY);
	}
	else
	{
		file = 0;
	}
		while(read(file, buff, 256))
		{
			//buff[255] = '\0';
			write(1,buff,256);
			//myprintf("%s",buff);
		}
	//myprintf("\n\0");
	/*}
	else
	{
		/hile(1)
		{
			mygets(buff);
			if(0 == strcmp(buff,"quit") || 0 == strcmp(buff,"exit"))
				break;
			myprintf("%s\n",buff);
		}
	}*/
}
