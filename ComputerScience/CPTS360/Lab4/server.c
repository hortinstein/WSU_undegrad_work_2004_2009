// This is the echo SERVER server.c

#define  MAX 256
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>

char* find_in_env(char *env[],char *look);
char* tokenize(char* var);
int handlecommand(char *command[5000],char *env[],char* dir_list[],int numdir);
int runcommand(char *env[],char* command);
char * WD_; //global for the $HOME directory
// Define variables:
struct sockaddr_in  server_addr, client_addr, name_addr;
struct hostent *hp;
char serveroutput[MAX];
int  sock, newsock;                  // socket descriptors
int  serverPort;                     // server port number
int  r, length, n;                   // help variables

// Server initialization code:

int server_init(char *name)
{
   printf("...server init\n");   
   // get DOT name and IP address of this host

   printf("...get and show server host info\n");
   hp = gethostbyname(name);
   if (hp == 0){
      printf("......unknown host\n");
      exit(1);
   }
   printf("...hostname=%s  IP=%s\n",
               hp->h_name,  inet_ntoa(*(long *)hp->h_addr));
  
   //  create a TCP socket by socket() syscall
   printf("...create a socket\n");
   sock = socket(AF_INET, SOCK_STREAM, 0);
   if (sock < 0){
      printf("......socket call failed\n");
      exit(2);
   }

   printf("...fill server_addr with host IP and PORT# info\n");
   // initialize the server_addr structure
   server_addr.sin_family = AF_INET;                  // for TCP/IP
   server_addr.sin_addr.s_addr = htonl(INADDR_ANY);   // THIS HOST IP address  
   server_addr.sin_port = 0;   // let kernel assign port

   printf("...bind socket to host info\n");
   // bind syscall: bind the socket to server_addr info
   r = bind(sock,(struct sockaddr *)&server_addr, sizeof(server_addr));
   if (r < 0){
       printf("......bind failed\n");
       exit(3);
   }

   printf("...find out Kernel assigned PORT# and show it\n");
   // find out socket port number (assigned by kernel)
   length = sizeof(name_addr);
   r = getsockname(sock, (struct sockaddr *)&name_addr, &length);
   if (r < 0){
      printf("......get socketname error\n");
      exit(4);
   }

   // show port number
   serverPort = ntohs(name_addr.sin_port);   // convert to host ushort
   printf("...Port=%d\n", serverPort);

   // listen at port with a max. queue of 5 (waiting clients) 
   printf("...server is listening ....\n");
   listen(sock, 5);
   printf("...init done\n");
}


main(int argc, char *argv[], char *env[])
{
   char *hostname, *temp_env[2000];
   char line[MAX],outputbuf[MAX];
	char *command,temp_command[MAX];
   if (argc < 2)
      hostname = "localhost";
   else
      hostname = argv[1];
 
   server_init(hostname); 

   // Try to accept a client request
   while(1){
     printf("...server: accepting new connection ....\n"); 

     // Try to accept a client connection as descriptor newsock
     length = sizeof(client_addr);
     newsock = accept(sock, (struct sockaddr *)&client_addr, &length);
     if (newsock < 0){
        printf("...server: accept error\n");
        exit(1);
     }
     printf("...server: accepted a client connection from\n");
     printf("        IP=%s  port=%d\n", inet_ntoa(client_addr.sin_addr.s_addr),
                                        ntohs(client_addr.sin_port));
     
     // Processing loop
     while(1){
       n = read(newsock, line, MAX);
       if (n==0){
           printf("......server: client died, server loops\n");
           close(newsock);
           break;
      		}
		strcpy(temp_env,env);	
		strcpy(temp_command,line);		
		//command = (strtok(temp_command," "));
		runcommand(temp_env,temp_command);
		
		printf("this is the output \n\n\n %s", serveroutput);
      // show the line string
      printf("...server: read  n=%d bytes; line=[%s]\n", n, line);

      strcat(line, " ECHO");
		
      // send the echo line to client 
      n = write(newsock, line, MAX);

      printf("...server: wrote n=%d bytes; ECHO=[%s]\n", n, line);
      printf("...server: ready for next request\n");
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
		printf("%s",serveroutput);
				i++;
			}
			if (i == numdir)
			{
				exit(3);//If it is not found it exits with 3
			}
				
		}
	
    }
   

}


