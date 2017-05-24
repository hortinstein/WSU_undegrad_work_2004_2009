#include <stdio.h>
#include <string.h>
#include <fcntl.h>    // for open()/close() syscalls


char* find_in_env(char *env[],char *look);
char* tokenize(char* var);
int handlecommand(char *command[5000],char *env[],char* dir_list[],int numdir);

char * WD_; //global for the $HOME directory
///main
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
		printf("   %s\n",dir_list[i]);
		i++;		
		dir_list[i] = (strtok(NULL, ":"));
		
		
	}
	numdir = i;
	
	strcpy(temp_command,command);
	i = 0;			
	printf("...tokenizing command and arguments\n");
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
			printf("%s ",parsed[i]);		
			i++;
		}
		printf("\n");
	}
	else if (strcmp(parsed[0],"cd") == 0)
	{	
		if(parsed[1] == '\0')
		{
			printf("...changing directory to %s \n",WD_);				
			chdir(WD_);//if no directory is given changes to $HOME found above
		}
		else if (parsed[2] != '\0')//checking for too many arguments
		{
			printf("...cd: too many arguments\n");
		}
		else
		{
			printf("...changing directory to %s \n",parsed[1]);
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
		printf("...searching for %s\n",look);
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
	printf("...Found %s\n", look);//WD_);

	return (WD_);
}


///handlecommand
///9/17/2007
///Finds the path of the commands for use later
///Lab3 of CS360
int handlecommand(char *command[5000],char *env[], char* dir_list[], int numdir)
{
	int i = 0,i2 =0,pid,status;	
	char temp_cmd[1000];
	 
	
	printf("...parent HortinShell %d forks\n", getpid());
	pid = fork();
	//while 	
	if (pid) 
	{ // parent:
		printf("...PARENT %d WAITS FOR CHILD %d TO DIE\n", getpid(),pid);
		pid=wait(&status);
        printf("...DEAD CHILD=%d, HOW=%04x\n", pid, status);
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
				printf("...I/O infile redirection value < found\n");
				fclose(stdin);				
				stdin = fopen(command[i2+1], "r");
				command[i2] = '\0';//erasing the redirection			
				break;
			} 
			else if(strcmp(command[i2],">") == 0)
			{
				printf("...I/O outfile redirection value > found\n");
				fclose(stdout);
				stdout = fopen(command[i2+1], "w");	
				command[i2] = '\0';//erasing the redirection				
				break;
			} 
			else if(strcmp(command[i2],">>") == 0)
			{
				printf("...I/O redirection value >> found\n");
				fclose(stdout);
				stdout = fopen(command[i2+1], "a");			
				command[i2] = '\0';//erasing the redirection				
				break;
			} 
			i2++;

		}
		    
		if (command[0][0] == '/')
		{
			printf("...executing program  in absolute path\n");
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
				printf("...trying %s\n",temp_cmd);
				execve(temp_cmd,command, env);
				i++;
			}
			if (i == numdir)
			{
				exit(3);//If it is not found it exits with 3
			}
		}
		printf("...child %d dies by exit(%d)\n", getpid(),status);
		       

    }
   

}

