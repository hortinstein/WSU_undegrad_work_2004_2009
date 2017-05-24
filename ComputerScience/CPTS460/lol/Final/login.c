//Daniel Rodgers
//CPTS 460
#include "ucode.c"
#include "io.c"
typedef struct lgn
{
	char user[10];
	char pass[10];
	char num1[2];
	char num2[1];
	char type[6];
	char usls[6];
	char home[32];
	char prog[10];
}LGN;
LGN login;

int token_user(line)char* line;
{
	strcpy(login.user, strtok(line, " :"));
	strcpy(login.pass, strtok(NULL, " :"));
	strcpy(login.num1, strtok(NULL, " :"));
	strcpy(login.num2, strtok(NULL, " :"));
	strcpy(login.type, strtok(NULL, " :"));
	strcpy(login.usls, strtok(NULL, " :"));
	strcpy(login.home, strtok(NULL, " :"));
	strcpy(login.prog, strtok(NULL, " :\n\r"));
}
char* tty;
int stdin, stdout, stderr;
main(argc, argv) int argc; char *argv[];   // invoked by exec("login /dev/ttyxx")
{
	int file,counter;
	unsigned short error = 0;
	char user_name[64];
	char user_pass[64];
	char line[128];
	char l[5];
	l[0] = 'c';
	//tty = (char*) malloc(sizeof(argv[1]));
	tty = argv[1];
	settty(tty);
  	// close 0, 1, 2 in case INIT opened them before
	close(0); close(1); close(2);
	stdin  = open(tty, O_RDONLY);	
	stdout = open(tty, O_WRONLY);
	stderr = open(tty, O_WRONLY);
	//
	//gettty(line);
	myprintf("tty = %s\n", argv[1]);
  	signal(2,1);  // syscall(51, 2, 1); ignore Control-C interrupts so that 

	myprintf("Welcome to (D)an's (O)perating (S)ystem Login\n");
  	while(1)
	{
		myprintf("\nDOS:> Input User Name: ");
		mygets(user_name);
		myprintf("DOS:> Input User Password: ");
		myget_password(user_pass);
		file = open("/etc/passwd", O_RDONLY);
		while(1)
		{
			counter = 0;
			while(l[0] != '\n')
			{
				if(0 == read(file,l,1))
				{
					//myprintf("Here\n");
					error = 1;
				}
				if(l[0] != '\n')
				{
					line[counter] = l[0];
					counter++;
				}
			}
			l[0] = '\0';
			line[counter] = '\0';

			token_user(line);

			if( strcmp(login.user, user_name) == 0 )
				break;			
		}
		//close the file
		close(file);
		//Check password
		if( error == 0)
		{
			if( strcmp(user_pass, login.pass) != 0 )
				error = 1;
		}
		if(error == 0)
		{
			setuid(login.num1);
			chdir(login.home);
			exec(login.prog);
			close(0); close(1); close(2);
			stdin  = open(tty, O_RDONLY);	
			stdout = open(tty, O_WRONLY);
			stderr = open(tty, O_WRONLY);
		}
		myprintf("DOS:> ERROR: BAD USER/PASSWORD\n");
		file = open("/etc/passwd", O_RDONLY);
		error = 0;
  	}
	myprintf("DOS:> ERROR: AN ERROR OCCURRED DOING LOGIN\n");
}
