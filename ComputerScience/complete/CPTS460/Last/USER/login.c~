//***********************************************************************
//                   LOGIC of login.c file
//***********************************************************************
#include "ucode.c"

char *tty;
int stdin, stdout, stderr;

char line[256];//a line out of the passwd file
char uattempt[16];
char pattempt[16];
USER login_user;//a structure to store the login user to

int parse_passwd(){
	int pass_file;//file descriptor for the passwd file
	char cur[10];
	int count = 0;
	pass_file = open("/etc/passwd",O_RDONLY);//opens up the passwd file for reading
	while (0 != read(pass_file,cur,1)){ //while the final line is not black
		line[count] = cur[0];	//for some reason read reads in more than 1 char, so this is nessecary				
				
		if  (cur[0] == '\n'){//a full record read in			
			printf("%s",line);//prints the current user that it's attempting to validate		
			if (	strcmp(uattempt,strtok(line," :")) == 0 && strcmp(pattempt,strtok('\0'," :")) ==0 ){
				printf("HortinLOGIN : access granted \n");//user found now copies all information to the user struct
				strcpy(login_user.uname,uattempt);
				strcpy(login_user.pword,pattempt);
				login_user.gid = atoi( strtok('\0'," :") );
				login_user.uid = atoi( strtok('\0'," :") );
				strcpy(login_user.fullname, strtok('\0',":"));
				strcpy(login_user.homedir,strtok('\0'," :"));
				strcpy(login_user.prog,strtok('\0'," :\n"));
				//printf("\n%s\n\n", strtok('\0'," :\n"));				
								
				close(pass_file);		
				return 1;
			}
			else{
				count = -1;		
			}
		}
		count++;
		cur[0] = '\0';
		
	}
	printf("HortinLOGIN : access denied\n ");	
	close(pass_file);
	return 0;
}



main(argc, argv) int argc; char *argv[];   // invoked by exec("login /dev/ttyxx")
{
	tty =  argv[1];
	//USER *attemp_log;
  	// close 0, 1 from parent INIT
  	close(0); close(1);

  	// open own tty as stdin, stdout, stderr
  	stdin  = open(tty, O_RDONLY);
  	stdout = open(tty, O_WRONLY);
  	stderr = open(tty, O_WRONLY);

  	fixtty(tty);   // store tty string in PROC.tty[] for putc()

  	// NOW we can use printf, which calls putc() to our tty
  	printf("HortinLOGIN : open %s as stdin, stdout, stderr\n", tty);

  	signal(2,1);// syscall(51, 2, 1); ignore Control-C interrupts so that Control-C KILLs other procs on this tty but not the main sh

	while(1){
	//    1. show login: to stdout
		printf("HortinLOGIN : login :"); 
	//    2. read user name from stdin
		gets(uattempt);		
	//    3. show passwd:
		printf("HortinLOGIN : password :"); 
	//    4. read user passwd
		gets(pattempt);
	//    5. verify user name and passwd from /etc/passwd file
	//    6. if (user account valid){
		if (parse_passwd() == 1){
	//          setuid to user uid.
			setuid(login_user.uid);		
	//          chdir to user HOME directory.
			chdir(login_user.homedir);	
	//          exec to the program in users's account
			printf("HortinLOGIN : running %s\n",login_user.uname);			
			exec(login_user.prog);
		}
	
	//       }
	//       printf("login failed, try again\n");
	//  }
	}
}

