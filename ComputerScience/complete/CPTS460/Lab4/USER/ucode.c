// ucode.c file

char *cmd[]={"getpid", "ps", "chname", "kmode", "switch", "wait", "exit","fork","exec", 0};

int show_menu()
{
   printf("***************** Menu *******************\n");
   printf("*  ps  chname  kmode  switch  wait  fork exec exit *\n");
   /*         1     2      3       4      5     6  */
   printf("******************************************\n");
}

int find_cmd(name) char *name;
{
   int i=0;   
   char *p=cmd[0];

   while (p){
         if (strcmp(p, name)==0)
            return i;
         i++;  
         p = cmd[i];
   } 
   return(-1);
}


int getpid()
{
   return syscall(0,0,0);
}

int ps()
{
   syscall(1, 0, 0);
}

int chname()
{
    char s[64];
    printf("\ninput new name : ");
    gets(s);
    syscall(2, s, 0);
}

int kmode()
{
    printf("kmode : syscall #3 to enter Kmode\n");
    printf("proc %d going K mode ....\n", mypid);
        syscall(3, 0, 0);
    printf("proc %d back from Kernel\n", mypid);
}    

int kswitch()
{
    printf("proc %d enter Kernel to switch proc\n", mypid);
        syscall(4,0,0);
    printf("proc %d back from Kernel\n", mypid);
}

int wait()
{
    int child, exitValue;
    printf("proc %d enter Kernel to wait for a child to die\n", mypid);
    child = syscall(5, &exitValue, 0);
    printf("proc %d back from wait, dead child=%d", mypid, child);
    if (child>=0)
        printf("exitValue=%d", exitValue);
    printf("\n"); 
} 

int exit()
{
   char exitValue;
   printf("\nenter an exitValue (0-9) : ");
   exitValue=getc() - '0';
   printf("enter kernel to die with exitValue=%d\n", exitValue);
        syscall(6,exitValue,0);
}
int fork()
{
	printf("\nforking : ");

	return syscall(7,0,0);

}
int exec()
{
    char s[64];
    printf("\ninput exec path : ");
    gets(s);
    syscall(8, s, 0);
}

int invalid(name) char *name;
{
    printf("Invalid command : %s\n", name);
}
