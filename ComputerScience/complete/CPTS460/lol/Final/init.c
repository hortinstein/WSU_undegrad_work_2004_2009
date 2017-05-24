//Daniel Rodgers
//Init

//*************************************************************************
//                      Logic of init.c 
// NOTE: this init.c creates only ONE login process on console=/dev/tty0
// YOUR init.c must also create login processes on serial ports /dev/ttyS0
// and /dev/ttyS1.. 
//************************************************************************

#include "ucode.c"
#include "io.c"

int pid, child, status, s0,s1;
int stdin, stdout;

int login()
{
	myprintf("Exec login\n");
	exec("login /dev/tty0");
}
int login_S0()
{
	exec("login /dev/ttyS0");
}
int login_S1()
{
	exec("login /dev/ttyS1");
}

main(argc, argv) int argc; char *argv[];
{
   // open /dev/tty0 for READ and WRTIE in order to display messages
   stdin  = open("/dev/tty0", O_RDONLY);
   stdout = open("/dev/tty0", O_WRONLY);
	

   // Now we can use printf, which calls putc(), which writes to fd=1
	myprintf("Starting Dans Initilizing process!\n");
   	child = fork();
	if(!child)
	{
 		login_S0();
	}
	child = fork();
	if(!child)
	{
 		login_S1();
	}	


   	myprintf("DANINIT: Forking a login task on console\n"); 
   	child = fork();
	if (child)
	{
		myprintf("calling parent\n");
		parent();
	}
   	else
	{
 		login();
	}
}       
int parent_s0()
{
	while(1)
	{
		myprintf("DANINIT : waiting .....\n");

		pid = wait(&status);

    	if (pid == child)
    	{
			myprintf("DANINIT: Logon process died, starting a new one\n");
			child = fork();
			if (child)
				parent();
   			else  /* login task */
 				login();
		}
    	else
       		myprintf("DANINIT : buried an orphan child %d\n", pid);
  	}
}

      
int parent()
{
	while(1)
	{
		myprintf("DANINIT : waiting .....\n");

		pid = wait(&status);

    	if (pid == child)
    	{
			myprintf("DANINIT: Logon process died, starting a new one\n");
			child = fork();
			if (child)
				parent();
   			else  /* login task */
 				login();
		}
    	else
       		myprintf("DANINIT : buried an orphan child %d\n", pid);
  	}
}

