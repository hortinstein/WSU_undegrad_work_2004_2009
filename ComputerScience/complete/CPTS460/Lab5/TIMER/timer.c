/* timer parameters. */
#define LATCH_COUNT     0x00	/* cc00xxxx, c = channel, x = any */
#define SQUARE_WAVE     0x36	/* ccaammmb, a = access, m = mode, b = BCD */

/************************ NOTICE THE DIVISOR VALUE ***********************/
#define TIMER_FREQ   1193182L	/* timer frequency for timer in PC and AT */
#define TIMER_COUNT ((unsigned) (TIMER_FREQ/60)) /* initial value for counter*/

#define TIMER0       0x40
#define TIMER_MODE   0x43
#define TIMER_IRQ       0

ushort seconds=0;
ushort minutes=0;
ushort hours=0;
int enable_irq(irq_nr) unsigned irq_nr;
{
  lock();
    out_byte(0x21, in_byte(0x21) & ~(1 << irq_nr));

}

/*===========================================================================*
 *				timer_init				     *
 *===========================================================================*/

ushort tick;

int timer_init()
{
  /* Initialize channel 0 of the 8253A timer to e.g. 60 Hz. */

  printf("timer init\n");
  tick = 0;

  out_byte(TIMER_MODE, SQUARE_WAVE);	/* set timer to run continuously */
  out_byte(TIMER0, TIMER_COUNT);	/* load timer low byte */
  out_byte(TIMER0, TIMER_COUNT >> 8);	/* load timer high byte */
  enable_irq(TIMER_IRQ); 
}

/*===========================================================================*
 *				timer_handler				     *
 *===========================================================================*/
////////////////////////////////////////////////////////////////////////////////////////
//thandler- this is the function that handles the timer interupts
//it calls a print function in the vid driver file to print out the time
//it also handles swithcing processes
////////////////////////////////////////////////////////////////////////////////////////
int thandler()
{
	PROC *p = sleepList;
	PROC *prev = running;	
	int i;
    tick++; 
    tick %= 60;
	if (tick % 60 == 0){
		seconds++;
	}
	if (seconds % 60 == 0 && tick % 60 == 0){
		minutes++;
		seconds = 0;
	}	
    	if (minutes % 60 == 0 && tick % 60 == 0 && seconds & 60 == 0 ){
		hours++;		
		minutes = 0;
	}	
	if (tick % 60 == 10 &&seconds % 5 == 0 && seconds % 10 == 0)
	{
		//printf("\nlight on");
		light_on();		
		out_byte(0x0C, 0x3F2);
	}
	else if(tick % 60 == 10 && seconds % 5 == 0)
	{
		
		//printf("\nlight off");
		light_off();		
		out_byte(0x0C, 0x3F2);
	}
if (tick % 60 == 0){
//		seconds++;
		while(p){
			//printf("\n\nPID %d alarmclock %d\n\n",p->pid,sleepcount[p->pid]--) ;
			sleepcount[p->pid]--;
			if (sleepcount[p->pid] == 0 && p->status == SLEEP)//for every task p SLEEPing on this event 	
			{
				// remove p from sleepList if you implement a sleepList
				p->status = READY;        // make it READY
				prev->next = p->next;	  // link the list		
				enqueue(p);                // enter it into a ready queue (by its pri)
				do_ps();				
				//tswitch();			
			}
			p = p->next;
		}
	}
	if (tick % 60 == 0 && inkmode != 2){//decrementing the running time for the running process only if in umode
		//printf ("%d",inkmode);		
		running->time--;
		if (running->time == 0 ){//processes allocated time is through			
			printf("\n");		
			out_byte(0x20, 0x20);//reenables the timer  			
			tswitch();			
		}	
	}    	
	if (tick % 60 == 0){//this ensures the time only updates per second       		
		print_time(seconds,minutes,hours);
		
		time_left(running->time);	
	}	
	
		
    out_byte(0x20, 0x20);  

}





