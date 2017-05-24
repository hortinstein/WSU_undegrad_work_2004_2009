
int kcinth()
{
   ushort seg, off, r;
   int    x, y, z, w;

   seg = running->uss; off = running->usp;

   x = get_word(seg, off + 2*13);
   y = get_word(seg, off + 2*14);
   z = get_word(seg, off + 2*15);
   w = get_word(seg, off + 2*16);

   switch(x){
       case 0 : r = running->pid;     break;
       case 1 : r = do_ps();          break;
       case 2 : r = chname(y);        break;
       case 3 : r = kmode();          break;
       case 4 : r = tswitch();        break;
       case 5 : r = do_wait(y);       break;
       case 6  : r = do_exit(y);      break;       
   
       case 7  : r = ufork();         break;
       case 8 :  r = exec(y);         break;
 
       case 9 : r = chcolor(y); break;

       case 10: r = putc(y); break;
	case 11: time_sleep(y); break;///this is my timed sleep function
       case 99 : do_exit(y);           break;
 
       default: printf("invalid syscall # : %d\n", x);
                break;
   }
   put_word(r, seg, off + 2*8);
}


//////////////////////////////////////////////////////////
//This function is meant to put the process that called it on the sleep list
//for a certain ammound of time
////
time_sleep(y)int y;
{
	PROC *curr;
	printf ("\n%d\n",y+150);
		
	sleepcount[running->pid] = 5;
	running->status = SLEEP;
	if (sleepList==0)//if the ready queue is empty
	{
    	sleepList = running;
	running->next = '\0';
	}  	
	else{
		curr = sleepList;
	    	while (curr->next!=0)//while there are still elements in the sleepqueue
		{
				curr = curr->next;
				if (curr == running)//if the next process is running break 
					break;		
		}
		curr->next = running;
		running->next = '\0';
				
  	}
	tswitch();                   // not in readyQueue anymore

}
//////////////////////////////////////////////////////////
