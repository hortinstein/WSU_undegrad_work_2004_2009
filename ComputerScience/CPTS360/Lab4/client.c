//**************************** ECHO CLIENT CODE **************************
// The echo client client.c

#define MAX 256

#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>

char* find_in_env(char *env[],char *look);
char* tokenize(char* var);
int handlecommand(char *command[5000],char *env[],char* dir_list[],int numdir);
int runcommand(char *env[],char* command);
char * WD_; //global for the $HOME directory

// Define variables
struct hostent *hp;              
struct sockaddr_in  server_addr; 

int sock, r;

int SERVER_IP, SERVER_PORT; 



// clinet initialization code

int client_init(char *argv[])
{
  printf("...clinet init\n");

  printf("...get server info\n");
  hp = gethostbyname(argv[1]);
  if (hp==0){
     printf("......unknown host %s\n", argv[1]);
     exit(1);
  }

  SERVER_IP   = *(long *)hp->h_addr;
  SERVER_PORT = atoi(argv[2]);

  printf("...create a TCP socket\n");
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock<0){
     printf("......socket call failed\n");
     exit(2);
  }

  printf("...fill server_addr with server's IP and PORT#\n");
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = SERVER_IP;
  server_addr.sin_port = htons(SERVER_PORT);

  // Connect to server
  printf("...connecting to server ....\n");
  r = connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (r < 0){
     printf(".......connect failed\n");
     exit(1);
  }

  printf("...connected OK to \007\n"); 
  printf("......hostname=%s  IP=%s  PORT=%d\n", 
          hp->h_name, inet_ntoa(SERVER_IP), SERVER_PORT);
  }

int main(int argc, char *argv[], char *env[])
{
	char *command, *localcmd,initialcmd[MAX];
	char *command_array = {"ls","-s"};
	char temp_command[5000], *parsed[5000];
	char temp_env[5000];
  int n,i=0;
  char line[MAX], ans[MAX];

  if (argc < 3){
     printf("...usage : client ServerName SeverPort\n");
     exit(1);
  }

  client_init(argv);

  printf("...processing loop\n");
  while (1){
	i = 0;	
	while (i < MAX)
	{
		line[i] = '\0';
		i++;
	}

	i=0;
	while (parsed[i] < 5000)//clearing all of the arguments for new call
	{
		
		parsed[i] = '\0';
		i++;
	}
	
    printf("......input a line : ");
    //fgets(line, 128, stdin);	
	gets(line);	
	printf("%s",line);
	///////////////////////////////////////////////////////
	////////////////////////MY CODE////////////////////////
	///////////////////////////////////////////////////////
	if (strlen(line) > 0){	
		strcpy(temp_command,line);
		i = 0;			
		parsed[i] = (strtok(temp_command," "));
		while (parsed[i] != '\0')
		{
			i++;
			parsed[i] = (strtok(NULL, " "));	
		}
		command = initialcmd;
		if (strcmp(parsed[0],"quit") == 0)
		{
			//n = write(sock, "", MAX);
			return 0;
		}	
		else if (strcmp(parsed[0],"lpwd") == 0 || strcmp(parsed[0],"lls") == 0 || strcmp(parsed[0],"lcd") == 0 || strcmp(parsed[0],"lmkdir") == 0 || 
			strcmp(parsed[0],"lrmdir") == 0 || strcmp(parsed[0],"lrm") == 0)
		{
			strcpy(temp_env,env);
			line[0] = ' ';
			runcommand(temp_env,line);	
		}
		else if (strcmp(parsed[0],"ls") == 0 || strcmp(parsed[0],"cd") == 0 || strcmp(parsed[0],"mkdir") == 0 || strcmp(parsed[0],"rmdir") == 0 ||
			strcmp(parsed[0],"rm") == 0 || strcmp(parsed[0],"get") == 0 || strcmp(parsed[0],"put") == 0) 
		{
			///////////////////////////////////////////////////////
			////////////////////////END////////////////////////////
			///////////////////////////////////////////////////////
		    //line[strlen(line)-1] = 0;        // kill <CR> at end
		    if (line[0]==0)                  // exit if NULL line
		       exit(0);

		    // Send line to server
		    n = write(sock, line, MAX);
		    printf("...client: wrote n=%d bytes; line=(%s)\n", n, line);
			
		    // Read a line from sock and show it
		    n = read(sock, ans, MAX);
		    printf("...client: read  n=%d bytes; echo=(%s)\n",n, ans);
		}
		i = 0;
	}
  }
}

///runcommand
///9/17/2007
///Emulates the BASH shell for the Unix environment
///Lab3 of CS360
int runcommand(char *env[],char* command)
{
	int i = 0,i2 = 0,found = 0,numdir = 0,iofind;
	char *PATH_,temp_command[5000], *parsed[5000],*dir_list[100];
	WD_ = find_in_env(env,"HOME");
	PATH_ = find_in_env(env,"PATH");
	FILE *redirectFile = NULL;
	//Seperating the Directories into different entries	
	dir_list[i] = (strtok((PATH_ + 5),":"));
	while (dir_list[i] != '\0')
	{
		i++;		
		dir_list[i] = (strtok(NULL, ":"));	
	}
	numdir = i;
	
	strcpy(temp_command,command);
	i = 0;			
	parsed[i] = (strtok(temp_command," "));
	while (parsed[i] != '\0')
	{
		i++;
		parsed[i] = (strtok(NULL, " "));	
	}
	
		
	i2=0;//resetting ints for finding function	
	i = 0;

	//handles the commands
	if (strcmp(parsed[0],"exit") == 0)
	{
		return 0;
	}
	else if (strcmp(parsed[0],"echo") == 0)//handles the echo command
	{	
		i++;		
		while(parsed[i] != '\0')
		{
			i++;
		}
	}
	else if (strcmp(parsed[0],"cd") == 0)
	{	
		if(parsed[1] == '\0')
		{
			chdir(WD_);//if no directory is given changes to $HOME found above
		}
		else if (parsed[2] != '\0')//checking for too many arguments
		{
			printf("...cd: too many arguments\n");
		}
		else
		{
			chdir(parsed[1]);//if a directory is stated than it changes to it
		}
	}
	else 
	{
		handlecommand(parsed,env,dir_list,numdir);
	}
	i=0;
	while (parsed[i] < 5000)//clearing all of the arguments for new call
	{
		i++;
		parsed[i] = '\0';
		
	}
}

///find_in_env
///9/17/2007
///finds an argument within env
///Lab3 of CS360
char* find_in_env(char *env[], char *look)
{
	int i = 0;
	int found = 0;
	char temp[5], *WD_;
	while (found != 1)//searching the env for arg
	{
		strncpy(temp,(char *)env[i],4);//looking for argin *env[]  
		//printf("%s\n", temp);		
		if (strcmp(temp, look) != 0)
		{
			found = 0;i++;
		}
		else
		{	
			found = 1;
		}
		
	}
	WD_= (char *)env[i];i=0;found=0;//setting and resettign cond variables
	return (WD_);
}


///handlecommand
///9/17/2007
///Finds the path of the commands for usint runcommand(char *env[],char* command)e later
///Lab3 of CS360
int handlecommand(char *command[5000],char *env[], char* dir_list[], int numdir)
{
	int i = 0,i2 =0,pid,status;	
	char temp_cmd[1000];
	pid = fork();
	//while 	
	if (pid) 
	{ // parent:
		pid=wait(&status);
    	return 0; 
    }
    else
	{ // child:		
		i2=0;//resetting ints for finding function	
		///////////////////////////////
		////Handle File Redirection////
		///////////////////////////////
				
		while(command[i2] != '\0')
		{	
			if(strcmp(command[i2],"<") == 0)
			{
				fclose(stdin);				
				stdin = fopen(command[i2+1], "r");
				command[i2] = '\0';//erasing the redirection			
				break;
			} 
			else if(strcmp(command[i2],">") == 0)
			{
				fclose(stdout);
				stdout = fopen(command[i2+1], "w");	
				command[i2] = '\0';//erasing the redirection				
				break;
			} 
			else if(strcmp(command[i2],">>") == 0)
			{
				fclose(stdout);
				stdout = fopen(command[i2+1], "a");			
				command[i2] = '\0';//erasing the redirection				
				break;
			} 
			i2++;

		}
		    
		if (command[0][0] == '/')
		{
			execve(command[0],command, env);
			exit(2);
		} 
		else
		{
			while(i < numdir)
			{	//Creating the program path name
				temp_cmd[0] = '\0';				
				//printf("...trying %s\n",dir_list[i]);
				strcat(temp_cmd, dir_list[i]);
				strcat(temp_cmd,"/");
				strcat(temp_cmd,command[0]); 
				execve(temp_cmd,command, env);
				i++;
			}
			if (i == numdir)
			{
				exit(3);//If it is not found it exits with 3
			}
		}
		       

    }
   

}


