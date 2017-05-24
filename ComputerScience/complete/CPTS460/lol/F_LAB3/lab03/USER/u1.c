int mypid, mysegment, cmdIndex, color;

#include "ucode.c"

main()
{
  char name[64];

  mypid = getpid();
  mysegment = getcs();
  color = 0x000A + (mypid % 6);

  while(1){

    printf("=====================================================\n");
    printf("PROC %d in Umode | segment = %x\n",mypid, mysegment);

    show_menu();

    printf("Input a command: ");
    gets(name);

    switch(find_cmd(name)){
           case 0 : getpid();   break;
           case 1 : ps();       break;
           case 2 : chname();   break;
           case 3 : kmode();    break;
           case 4 : kswitch();  break;
           case 5 : wait();     break;
           case 6 : exit();     break;

           default: invalid(name); break;
    }
  }
}
