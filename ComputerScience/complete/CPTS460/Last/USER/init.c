//*************************************************************************
//                      Logic of init.c 
// NOTE: this init.c creates only ONE login process on console=/dev/tty0
// YOUR init.c must also create login processes on serial ports /dev/ttyS0
// and /dev/ttyS1.. 
//************************************************************************

int pid, child, status;
int stdin, stdout;

#include "ucode.c"

int login_shell1()
{
    exec("login /dev/tty0");
}

int login_serial1()
{
    exec("login /dev/ttyS0");
}

int login_serial2()
{
    exec("login /dev/ttyS1");
}
main(argc, argv) int argc; char *argv[];
{
   // open /dev/tty0 for READ and WRTIE in order to display messages
   stdin  = open("/dev/tty0", O_RDONLY);
   stdout = open("/dev/tty0", O_WRONLY);

   	//This block of code creates the login for the two serial machines	
	child = fork();
	if (child){//if it child process than it will load serial port 1 in for use 
		printf("HortinINIT : fork a login task for serial 1\n");        			
		login_serial1();		
	}
   	child = fork();
	if (child){//if it is the child process it will load serial port 2 in for use
		printf("HortinINIT : fork a login task for serial 2\n");        					
		login_serial2()	;	
	}	   


	//This block of code creates the login for the local machine	
	child = fork();
	if (child){
		parent();//this sets up a loop in which there will a process to fork login machines (loop?)
	}
   	else { /* login task */
       		login_shell1();
	}
}      

//This function is called for p0 to wait in      
int parent()
{
  while(1){
	printf("HortinINIT : waiting .....\n");
	pid = wait(&status);//puts the parent to sleep waiting for it's child to return
	//if pid == child  	
	if (pid == child){
		printf("HortinINIT : forking another login child .....\n");    
		//This block of code creates the login for the local machine	
		child = fork();
		if (child){
			parent();//this sets up a loop in which there will a process to fork login machines (loop?)
		}
	   	else { /* login task */
	       		login_shell1();
		}
   			
	}    		
	else{
    		printf("HortinINIT: buried an orphan child %d\n", pid);//this will show the process died than loop around to make another login
	}
  }
}


