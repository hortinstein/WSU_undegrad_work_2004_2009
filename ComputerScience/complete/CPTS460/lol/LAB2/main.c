//Daniel Rodgers

#define NTASK    10                /* number of task in proc array*/
#define SSIZE  1024                /* kstack int size */

#define DEAD      0                /* proc status     */
#define READY     1      

typedef struct proc
{
	struct proc *next;   
	int ksp;               /* saved sp; offset = 2 */
	int pid;
	int ppid;
	short priority;
	int status;            /* READY|DEAD, etc */
	int kstack[SSIZE];     // kmode stack of task
}PROC;


#include "io.c"   // YOUR IO.C file with prints, printi, myprintf, etc

PROC mainProc;
PROC proc[NTASK];
PROC *running = NULL;
PROC *readystack = NULL;
PROC *freestack = NULL;
int procSize = sizeof(PROC);
int pidcounter = 1;
/****************************************************************
 Initialize the proc's as shown:
        running ---> mainProc --> proc[0];
        the proc's as a circular list:
            proc[0] --> proc[1] ... --> proc[N-1] -->
              ^                                     |
              |<-----------------------------------<-
       Each task's kstack contains:
       PC, ax, bx, cx, dx, bp, si, di, flag;  all 2 bytes
*****************************************************************/
int body();  
//create a new proccess and add to ready
int myfork(p)int p;
{
	PROC* temp;
	PROC* curr;
	PROC* prev;
	int j = 0;
	if (freestack == NULL)
	{
		myprintf("FAILED FORK\n");
		return 1;
	}
	if (readystack == NULL)
	{
		readystack = freestack;
		freestack = freestack->next;
		readystack->next = readystack;
		running->next = readystack;
		readystack->status = READY;
		for (j=1; j<10; j++)
  			readystack->kstack[SSIZE - j] = 0;
    	readystack->kstack[SSIZE-1]=(int)body;
    	readystack->ksp = &(readystack->kstack[SSIZE-9]);
		return 0;
	}
	else
	{
		temp = freestack;
		freestack = freestack->next;
		curr = readystack;
		prev = running;
		while(curr->priority >= p)
		{
			prev = curr;
			curr = curr->next;
			if (curr == running)
				break;
		}
		temp->next = curr;
		prev->next = temp;
		temp->priority = p;
		temp->status = READY;
		temp->ppid = running->pid;
		for (j=1; j<10; j++)
  			temp->kstack[SSIZE - j] = 0;
    	temp->kstack[SSIZE-1]=(int)body;
    	temp->ksp = &(temp->kstack[SSIZE-9]);
		return 0;
	}
}
int initialize()
{
	int i, j;
  	PROC *p;

  	running = &mainProc;
	//Setup Main proc
	running->next = NULL;
  	running->pid = 0;
	running->priority = -1;
  	running->status = READY;
  	for (i=0; i < NTASK; i++)
	{
    	p = &proc[i];

    	p->next= &proc[i+1];
    	p->pid = i+1;                           
    	p->status = READY;
    	
  	}
  	p->next = NULL;
	freestack = &proc[0];
	readystack = NULL;
	myfork(0);
	//tswitch();
  	myprintf("initialization complete\n");
}
/*
for (j=1; j<10; j++)
      		p->kstack[SSIZE - j] = 0;

    	p->kstack[SSIZE-1]=(int)body;
    	p->ksp = &(p->kstack[SSIZE-9]);
*/
char *gasp[NTASK]={
     "Oh! You are killing me .......",
     "Oh! I am dying ...............", 
     "Oh! I am a goner .............", 
     "Bye! Bye! World...............",      
};

int grave()
{
	myprintf("\n*****************************************\n"); 
	myprintf("Task %d: WHY! OH GOD IT BURNS\n",running->pid);
  	myprintf("*****************************************\n");
  	running->status = DEAD;
	running->ppid = -1;
	running->priority = -1;
  	tswitch();   /* journey of no return */        
}
//bring out your dead
int grave_robber()
{
	PROC* c;
	PROC* p;
	PROC* t;
	c = running;
	c = c->next;
	p = running;
	while(c != running)
	{
		if (c->status == DEAD)
		{
			change_ppid(c->pid);
			t = c;
			p->next = c->next;
			c = c->next;
			t->next = freestack;
			freestack = t;
		}
		else
		{
			p = c;
			c = c->next;
		}
	}
}
int change_ppid(x) int x;
{
	PROC* p = running;
	if (p->ppid == x)
		p->ppid = mainProc.pid;
	p = p->next;
	while (p != running)
	{
		if(p->ppid = x)
			p->ppid = mainProc.pid;
		p = p->next;
	}
}
int ps()  // print READY tasks
{
  	PROC *p;

  	p = running;
	myprintf("\n...........................\nReady Stack\n...........................\nTOP------>BOTTOM\n");
  	myprintf("Running = %d->\n", p->pid);

  	p = p->next;

  	while(p != running && p->status == READY )
	{
		if( p != running->next)
			myprintf("->");
    	myprintf("%d", p->pid);
    	p = p->next;
  	}
  	myprintf("\n...........................\n");
}
int pf()  // print free tasks
{
  	PROC *p;

  	p = freestack;
  	myprintf("\n...........................\nFree Stack\n...........................\nTOP------>BOTTOM\n");
  	while(p != NULL)
	{
		if(p != freestack)
			myprintf("->");
    	myprintf("%d", p->pid);
    	p = p->next;
  	}
  	myprintf("\n...........................\n");
}
int body()
{  
	char c;
	grave_robber();
   	while(1)
	{
       	myprintf("====================\nCurrent Running Task: %d\n====================\n", running->pid);
       	myprintf("Input a char: \nr:view ready queue\nf:view free\nk:kill current process\nn:fork new process\ns:switch to next process\n");
	 	c=getc();
       	switch(c)
		{
			case 'r': ps(); break;
			case 'f': pf(); break;
			case 'k': grave(); break;
            case 'n': myfork(1);   break;
			case 's': tswitch(); break;
            default :            break;  
       }
   }
}


main()
{
	myprintf("\nWelcome to the 460 Multitasking System\n");
   	initialize();
   	tswitch();
 	myprintf("all dead, happy ending\n");
}


int scheduler()
{
    PROC *p;
    p = running->next;
	
    while (p->status != READY && p != running)
      p = p->next;

    if (p == running)
       running = &mainProc;
    else
       running = p;
/*
    myprintf("\n-----------------------------\n");
    myprintf("next running task = %d\n", running->pid);
    myprintf("-----------------------------\n");*/
}
