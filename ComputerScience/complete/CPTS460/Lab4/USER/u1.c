int mypid, mysegment, cmdIndex, color;

#include "ucode.c"

main()
{ 
  char name[64]; 

  mypid = getpid();
  mysegment = getcs();
  color = 0x000A + (mypid % 6);

  while(1){
       
    printf("==============================================\n");
    printf("I am proc %din U mode: running at segment=%x\n",mypid, mysegment);
    show_menu();
    printf("Command ? ");
    gets(name); 
    if (name[0]==0) 
        continue;

    cmdIndex = find_cmd(name);
    switch(cmdIndex){
           case 0 : getpid();   break;
           case 1 : ps();       break;
           case 2 : chname();   break;
           case 3 : kmode();    break;
           case 4 : kswitch();  break;
           case 5 : wait();     break;

           case 6 : exit();      break;
	case 7 : fork();      break;
	case 8 : exec();
           default: invalid(name); break;
    }
  }
}
