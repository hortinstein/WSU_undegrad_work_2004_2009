int pid, me, status;
int num = 0; 
char cmdLine[64];
char parsedLine[20][16];
int pd[2];//for the pips
#include "ucode.c"       /* contains syscall functions */
#define O_RDONLY	     00
#define O_WRONLY	     01
#define O_RDWR		     02
#define O_CREAT		   0100	/* not fcntl */
#define O_TRUNC		  01000	/* not fcntl */
#define O_APPEND	  02000

int menu()
{
  printf("#############################################################\n");
  printf("#  ls       cd     pwd    cat   more    cp     mv   >   >>  #\n");
  printf("#  mkdir    rmdir  creat  rm    chmod   chown  lpr  <   |   #\n");
  printf("#############################################################\n");
}
///////////////////////
//This function tokenizes the command line into a parsed line of commands
///////////////////////
token(cmd) char * cmd;
{
	char* tmp;
	int numargs = 0;
	char copy[64];
	strcpy(copy,cmd);
	tmp = strtok(copy, " "); 
	while( tmp != '\0')
	{
		strcpy(parsedLine[numargs++],tmp);
		tmp = strtok('\0', " ");
	}
	strcpy(parsedLine[numargs],'\0');	
	num = numargs;
}
int execChild(cmd) char * cmd;
{
	pid = fork();
     	if (pid){
        	printf("...parent sh waits for child to die\n");
        	pid = wait(&status);
     
	}
     	else{
         	printf("...child task %d exec to %s\n", getpid(), parsedLine[0]);
            	exec(cmd);
         	printf("...exec failed\n");//child failed exiting!
	}
}

int parseRedirect(cmd,ischild) char * cmd; int ischild;
{
	char  *head, *tail;
	int numarg = 0,i2=0,i3,newcmdi=0,redir = 0,isorig=0,pid_redux;
	int pd[2];
	//printf("\nunparsed command %s\n",cmd);
	head = cmd;tail = cmd;	
	while (*tail != '\0'){
		if (*tail == '>' && *(tail + 1) == '>')
		{
			*tail = '@';
			*(tail+1) = ' '; 
		}
		tail++;
			
	}
			
	while (head != tail){
		//printf("\n%s\n",head);
		//this line is to see if redirection is found if it is the tail of command is removed and this is called recursively
		if (*tail == '<' ||*tail == '|' ||*tail == '>' ||*tail == '@'){
			redir = 1;		
////////////////////////////////////Forking the child for redirection////////////////////////						
			pid = fork();
     			if (pid){
					
        				pid = wait(&status);
					printf ("dead fin");			
			}
     			else{
/////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////changing the std io based on instruction/////////////////						
				//printf("...child task %d exec to %s\n", getpid(), parsedLine[0]);
				if (*tail == '<'){
					*tail = '\0';					
					tail = tail + 2;
					close(0);//closing stdin
					open(tail, O_RDONLY);		
					parseRedirect(cmd,1);
					
					exit(0);
				}
				if (*tail == '>'){
					*tail = '\0';						
					tail = tail + 2;
					printf("REDIR %s",cmd);				
					close(1);//closing stdout
					open(tail, O_WRONLY|O_CREAT);
					parseRedirect(head,1);									
					exit(0);
				}
				if (*tail == '@'){
					*tail = '\0';					
					tail = tail + 2;
					close(1);//closing stout
					open(tail, O_WRONLY|O_APPEND);
					parseRedirect(head,1);
					exit(0);  
				}         
				if (*tail == '|' ){
					*tail = '\0';					
					tail = tail + 2;
					//printf("...writer forking reader (writer | reader) ");
				    	pipe(pd);
					pid_redux = fork();
					if (pid_redux){// reader
						close( pd[1]);//readers close pd[1]
												
						close (0);//closing the stdin descriptor
						dup(pd[0]);//opens up another file descriptor									
						exec(tail);
						return;							
						//parseRedirect(cmd+newcmdi+2,i2,1);
					
					}			
					else {//writer
						close(pd[0]);//writers close pd[0]
						close (1);//closes the write
						dup(pd[1]);//opens up another file descriptor		
						parseRedirect(head,1);
						exit(0);
				 	} 
				}          								
			}					
		}	
		tail--; 	
	}
	if (redir == 1)
		return;
	else if (ischild ==1)
		exec(cmd);
	else 
		execChild(cmd);	
}
main(argc, argv) int argc; char *argv[];
{
  me = getpid();
  printf("HortinSHell: Enter ? for help menu\n");
  	while(1){
     		printf("\nHortinSHell: $");
     		gets(cmdLine);
     		if (cmdLine[0]==0)//no input
        	 	continue;
		/////////////////////////////
		//Checks for processes that can be executed within the current umode
		/////////////////////////////	
		token(cmdLine);   /* break up cmdLine into parsedLine[0], parsedLine[1],.... */
		if (strcmp(parsedLine[0], "?")==0 || strcmp(parsedLine[0], "help")==0){//prints the menu
	       		menu();
	    	}
		else if (strcmp(parsedLine[0], "logout")==0)//logs the user out
		 	exit(0);
		else if (strcmp(parsedLine[0], "cd")==0)//checks to see if the directory must be changed
		{
			chdir(parsedLine[1]);
			
		}
		else
        		parseRedirect(cmdLine,0);
     /****************************************************************
        NOTE: some commands, e.g. cd, MUST be done by sh itself.
              OTHER commands will be done as shown below:
      ****************************************************************/
        
     /***** fork a child to execute the command ******/
     		
	
  	}
}


