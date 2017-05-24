#include "io.c"        // YOUR io.c file
#include "ucode.c"      // GIVEN

int main()
{ 
  char name[64]; 
  int pid, cmd;

  while(1){
       pid = getpid();
       prints("==============================================\n");
       prints("I am proc %din U mode: running at segment=%x\n",
                getpid(), getcs());
       show_menu();
       prints("Command ? ");
       mygets(name); 

       if (name[0]==0) 
           continue;

       cmd = find_cmd(name);
       switch(cmd){
           case 0 : getpid();   break;
           case 1 : ps();       break;
           case 2 : chname();   break;
           case 3 : kmode();    break;
           case 4 : kswitch();  break;   // switch is a KEYWORD of C
           case 5 : wait();     break;
           case 6 : die();      break;
           default: invalid(name); break;
       }
  }
}
