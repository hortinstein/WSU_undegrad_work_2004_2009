//Daniel Rodgers

#include "ucode.c"
#include "io.c"   // YOUR IO.C file with prints, printi, myprintf, 

char cmdLine[64];
char buf[32];
char* name[20];
int pd[2];


int token_cmd(pathname)char* pathname;
{
    char* tp;
    int counter = 0;
	char copy[64];
	strcpy(copy,pathname);
	counter = 0;
    tp = strtok(copy, " "); 
    while( tp != NULL)
    {
        name[counter] = tp;
        counter++;
        tp = strtok(NULL, " ");
    }
    name[counter] = "";
}
int menu()
{
  	myprintf("////////////////////////////////\n");
	myprintf("/ ls      cd      pwd    cat   /\n");   
	myprintf("/ more    cp      mv     chmod /\n");
  	myprintf("/ mkdir   rmdir   creat  rm    /\n");
	myprintf("/ chown   lpr    <  |  <<  > ? /\n");
 	myprintf("////////////////////////////////\n");
}
void ex(cmd)char* cmd;
{
	int pid, status;
	myprintf("DASH: Forking to execute command:%s\n",cmd);
	pid = fork();
	if (pid)
	{
		myprintf("DASH: Parent sh %d waits for child to die\n",getpid());
		pid = wait(&status);
	}
	else
	{
		myprintf("DASH: child task %d exec to %s\n", getpid(), cmd);
		exec(cmdLine);
		myprintf("DASH: EXEC HAS FAILED ME\n");
	}
}
void check_redirect(cmd)char* cmd;
{
	int pid,pid2, status;
	int i = 0;
	int i2 = 0;
	int pd[2];
	char c;
	char c2;
	char cmd1[32];
	char cmd2[32];
	char shell[32];
	shell[0] = 's';
	shell[1] = 'h';
	shell[2] = ' ';
	shell[3] = '\0';

	c = cmd[i];
	while(c != '\0')
	{
		if(c == '<' || c == '|' || c == '>')
			break;
		i++;
		c = cmd[i];
	}
	if( c == '\0' )
		ex(cmd);
	else
	{
		myprintf("DASH: I/O REDIRECT STATEMENT DETECTED\n");
		i2 = 0;
		while(i2 != i)
		{
			cmd1[i2] = cmd[i2];
			i2++;
		}
		if(cmd[i2] == ' ')
			cmd1[i2-2] = '\0';
		else
			cmd1[i2] = '\0';
		if( c == '>' && cmd[i+1] == '>')
		{
			c = '^';
			i++;
		}
		i++;		
		while(cmd[i] == ' ' )
			i++;
		i2 = 0;
		while(cmd[i+i2] != '\0')
		{
			cmd2[i2] = cmd[i+i2];
			i2++;
		}
		cmd2[i2] = '\0';
		myprintf("DASH: Forking to execute command:%s\n",cmd);
		pid = fork();
		if (pid)
		{
			myprintf("DASH: Parent sh %d waits for child to die\n",getpid());
			pid = wait(&status);
		}
		else
		{
			i = 0;
			c2 = cmd2[i];
			while(c2 != '\0')
			{
				if(c2 == '<' || c2 == '|' || c2 == '>')
				{
					strcat(shell,cmd2);
					pid = fork();
					if(pid)
					{
						myprintf("DASH: Parent sh %d waits for child to die\n",getpid());
						pid = wait(&status);
					}
					else
					{
						exec(shell);
					}

				}
				i++;
				c2 = cmd2[i];
			}
			if( c == '|')
			{
				//readers close pd[1]
				//writers close pd[0]
				pid = fork();
				if(pid)
				{
					pid = wait(&status);
				}
				else
				{
					pipe(pd);
					pid2 = fork();
					if(pid2)
					{
						close(1); //stdour
						close(pd[0]);
						dup(pd[1]);
						exec(cmd1);
					}
					else
					{
						close(0);
						close(pd[1]);
						dup(pd[0]);
						//exec(cmd2);
						check_redirect(cmd2);
					}
				}
			}
			else
			{
				if(c == '>')
				{
					close(1);
					open(cmd2, O_WRONLY|O_CREAT);
				}
				else if( c == '<')
				{
					close(0);
					open(cmd2, O_RDONLY);
				}
				else if( c == '^')
				{
					close(1);
					open(cmd2, O_WRONLY|O_APPEND);
				}

				exec(cmd1);
				myprintf("DASH: EXEC HAS FAILED ME\n");
			}
		}
	}
}

main(argc, argv) int argc; char *argv[];
{
	int pid, me, status;
	me = getpid();
	//execute command passed to shell
	if (argc > 1)
	{
		myprintf("DASH: CHILD SH %d PROCESSING %s\n",me, argv[1]);
		exec(argv[1]);
		//myprintf("here")
	}
	myprintf("Welcome to (DA)ns (SH)ell!, DASH\n");
	menu();
	while(1)
	{
		myprintf("DASH: ");
		mygets(cmdLine);
		if (cmdLine[0]==0)
			continue;
		token_cmd(cmdLine);

		myprintf("%s\n",name[0]);
		myprintf("%s\n",name[1]);

		if (strcmp(name[0], "?")==0 || strcmp(name[0], "help")==0)
		{
			menu();
			continue;
		}
		if (strcmp(name[0], "logout") == 0)
			exit(0);
		if (strcmp(name[0], "pwd") == 0)
		{
			getcwd(buf);
			myprintf("%s\n",buf);
		}
		else if (strcmp(name[0], "cd") == 0 )
		{
			if(strcmp(name[1],"") != 0 && strcmp(name[1],".") != 0)
			{
				chdir(name[1]);
			}
		}
		else
		{
			check_redirect(cmdLine);
 		}
	}
}

