// ucode.c file

char *cmd[]={"getpid", "ps", "chname", "kmode", "switch", "wait", "die", 0};

int show_menu()
{
   prints("***************** Menu ******************\n");
   prints("*  ps  chname  kmode  switch  wait  die *\n");
   prints("*****************************************\n");
}

int find_cmd(name) char *name;
{
   int i;   char *p;
   i = 0;   p = cmd[0];
   while (p){
         if (strcmp(p, name)==0)
            return i;
         i++;  p = cmd[i];
   } 
   return(-1);
}


int getpid()
{
   return syscall(0,0,0,0);
}

int ps()
{
   syscall(1, 0, 0, 0);
}

int chname()
{
    char s[64];
    prints("input new name : ");
    mygets(s);
    syscall(2, s, 0, 0);
}

int kmode()
{
    prints("kmode : enter Kmode via INT 80\n");
    prints("proc %d going K mode ....\n", getpid());
        syscall(3, 0, 0, 0);
    prints("proc %d back from Kernel\n", getpid());
}    

int kswitch()  
{
    prints("proc %d enter Kernel to switch proc\n", getpid());
        syscall(4,0,0,0);
    prints("proc %d back from Kernel\n", getpid());
}

int wait()
{
    int child, exitValue;
    prints("proc %d enter Kernel to wait for a child to die\n", getpid());
    child = syscall(5, &exitValue, 0, 0);
    prints("proc %d back from wait, dead child=%d exitValue=%d\n",
            getpid(), child, exitValue); 
}

int die()
{
   char exitValue;
   prints("enter an exitValue (0-9) : ");
   exitValue=getc() - '0';
   prints("enter kernel to die with exitValue=%d\n");
   syscall(6,exitValue,0,0);
}


int invalid(name) char *name;
{
    prints("Invalid command : %s\n", name);
}/**/
