//Daniel Rodgers
//CPTS 460
//LAB 3
#define NTASK    10                /* number of task in proc array*/
#define SSIZE  1024                /* kstack int size */

#define DEAD      0                /* proc status     */
#define READY     1      
#define ZOMBIE    2
#define SLEEP     3

typedef struct proc
{
	struct proc *next;   
	int ksp;               /* saved sp; offset = 2 */
	int pid;
	int ppid;
	short priority;
	int event;
	int exitstatus;
	int status;            /* READY|DEAD, etc */
	int kstack[SSIZE];     // kmode stack of task
}PROC;

#include "io.c"

PROC mainProc;
PROC proc[NTASK];
PROC *running = NULL;
PROC *readystack = NULL;
PROC *freestack = NULL;
PROC *sleepstack = NULL;

int procSize = sizeof(PROC);
int pidcounter = 1;
int body();
int change_ppid(x) int x;
{
	PROC* p = running;
	if (p->ppid == x)
		p->ppid = 1;
	p = p->next;
	while (p != running)
	{
		if(p->ppid == x)
			p->ppid = 1;
		p = p->next;
	}
}
int mywait(status) int *status;
{
	int flag = 0;
	int i;
	int id = running->pid;
	for( i = 0; i < NTASK; i++)
	{
		if ( proc[i].ppid == id)
		{
			flag = 1;
       	}
	}
	if (flag == 0)
		return -1;
	//myprintf("here\n");
	while(1)
	{
		for( i = 0; i < NTASK; i++)
		{
			//myprintf("here\n");
			if ( proc[i].ppid == id && proc[i].status == ZOMBIE)
			{
				myprintf("\n*****************************************\n"); 
				myprintf("Task %d's Zombie existence has ended\n",proc[i].pid);
	  			myprintf("*****************************************\n");
				status = &proc[i].exitstatus;
        	    proc[i].status = DEAD;
				running->status == READY;
				running->event = -1;
        	    return proc[i].pid;
        	}
			   // sleep at its own &PROC
		}
		sleepy(running->pid); 
	}
}
int sleepy(event) int event;
{
	running->event = event;
	running->status = SLEEP;
	tswitch();
}

int wakeup(event) int event;
{
	PROC* temp;
	PROC* c = sleepstack;
	PROC* p = NULL;
	PROC* c2;
	PROC* p2;
	while(c != NULL)
	{
		if (c->event == event)
		{
			temp = c;
			temp->status = READY;
			if(p == NULL)
			{
				sleepstack = c->next;
				c = sleepstack;
				p = NULL;
			}
			else if(c->next == NULL)
			{
				p->next = NULL;
				c = NULL;
			}
			else
			{
				c = c->next;
				p->next = c;
			}
			if( running->next == running)
			{
				readystack = temp;
				running->next = temp;
				temp->next = running;
			}
			else
			{
				c2 = readystack;
				p2 = running;
				while(c2->priority >= p)
				{
					p2 = c2;
					c2 = c2->next;
					if (c2 == running)
						break;
				}
				myprintf("7\n");
				temp->next = c2;
				p2->next = temp;
			}
		}
		else
		{
			p = c;
			c = c->next;
		}
	}
}
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
		readystack->ppid = running->pid;
		for (j=1; j<10; j++)
  			readystack->kstack[SSIZE - j] = 0;
    	readystack->kstack[SSIZE-1]=(int)body;
    	readystack->ksp = &(readystack->kstack[SSIZE-9]);
		return readystack->pid;
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
		return temp->pid;
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
		p->ppid = -1;                           
    	p->status = DEAD;
    	
  	}
  	p->next = NULL;
	freestack = &proc[0];
	readystack = NULL;
	myfork(0);
	proc[0].next = &proc[0];
  	myprintf("Initialization Complete, %d proc's made\n", NTASK);
}
int grave()
{
	int i = 0;
	if (running->pid == 1)
	{
		for( i = 0; i < NTASK;i++)
		{
			if(proc[i].ppid == 1)
			{
				myprintf("Cant kill task1 while it still has running process!\n");
				return -1;
			}
		}
	}

	if(proc[running->ppid-1].status == SLEEP)
	{  	
		//myprintf("MAKING A ZOMBIE\n");
		running->status = ZOMBIE;
		wakeup(running->ppid);
	}
	else
	{
		myprintf("\n*****************************************\n"); 
		myprintf("Task %d: WHY! OH GOD IT BURNS\n",running->pid);
	  	myprintf("*****************************************\n");
		wakeup(running->pid);
		running->status = DEAD;		
	}
	change_ppid(running->pid);
  	tswitch();
}

//Enter Sandman
int sand_man()
{
	PROC* c;
	PROC* p;
	PROC* t;
	c = running;
	c = c->next;
	p = running;
	while(c != running)
	{
		if (c->status == SLEEP)
		{
			t = c;
			p->next = c->next;
			c = c->next;
			t->next = sleepstack;
			sleepstack = t;
		}
		else
		{
			p = c;
			c = c->next;
		}
	}
}

//dont fear the reaper
int grave_robber()
{
	PROC* c;
	PROC* p;
	PROC* t;
	int i;
	int flag = 0;
	c = running;
	c = c->next;
	p = running;
	while(c != running)
	{
		if (c->status == DEAD)
		{
			c->ppid = -1;
			c->event = -1;
			c->exitstatus = -1;
			t = c;
			p->next = c->next;
			c = c->next;
			t->next = freestack;
			freestack = t;
		}
		/*else if(c->status == ZOMBIE)
		{
			flag = 0;
			t = c;
			for(t = t->next; t != c;t = t->next)
			{
				if( t->event == c->ppid && t->status == SLEEP)
					flag = 1;
			}
			myprintf("proc[%d] status %d", c->ppid, proc[c->ppid].status);
			if (proc[c->ppid].event == SLEEP)
			{
				flag = 1;
			}
			if( flag == 0 )
			{
				c->status = DEAD;
				c->ppid = -1;
				c->event = -1;
				c->exitstatus = -1;
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
		}*/
		else
		{
			p = c;
			c = c->next;
		}
	}
}
int ps() //print all procs
{
	int i = 0;
	myprintf("\n...........................\nTask Stack\n...........................\nPID PPID STATUS\n");
 	for(i = 0; i<NTASK; i++)
	{
		myprintf("%d %d ", proc[i].pid, proc[i].ppid);
		if( proc[i].status == DEAD)
			myprintf("DEAD\n");
		else if( proc[i].status == READY)
			myprintf("READY\n");
		else if (proc[i].status == ZOMBIE)
			myprintf("ZOMBIE\n");
		else
			myprintf("SLEEP\n");
	}
	myprintf("\n");
}
int pr()  // print READY tasks
{
  	PROC *p;

  	p = running;
	myprintf("\n...........................\nReady Stack\n...........................\nTOP------>BOTTOM\n");
 	myprintf("\n"); 	
	myprintf("%d->", p->pid);

  	p = p->next;

  	while(p != running && p->status == READY )
	{
		if( p != running->next)
			myprintf("->");
    	myprintf("%d", p->pid);
    	p = p->next;
  	}
  	myprintf("\n");
}
int pl()
{
  	PROC *p;

  	p = sleepstack;
  	myprintf("\n...........................\nSleep Stack\n...........................\nPID(EVENT)\n");
  	while(p != NULL)
	{
    	myprintf("%d(%d)\n", p->pid,p->event);
    	p = p->next;
  	}
  	myprintf("\n");
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
	char* e;
	int n;
	int* x;
   	while(1)
	{
		grave_robber();
		sand_man();
       	myprintf("====================\nCurrent Running Task: %d\n====================\n", running->pid);
       	myprintf("Input a char: \np:print all procs\nk:kill current process\nf:fork new process\ns:switch to next process\n");
		myprintf("z:put current process to sleep\nr:print ready stack\ne:print free stack\nl:print sleep list\nw:wakeup\n");
		myprintf("a:wait\n");
	 	c = getc();
       	switch(c)
		{
			case 'p': ps(); break;
			case 'k': grave(); break;
            case 'f': myfork(1); break;
			case 's': tswitch(); break;
			case 'l': pl(); break;
			case 'r': pr(); break;
			case 'e': pf(); break;
			case 'z': 
				myprintf("Sleep on what event?\n");
				mygets(e);
				sleepy(atoi(e)); 
				break;
			case 'w': 
				myprintf("a:all 1-%d\n",NTASK);
				myprintf("Event to wakeup?");
				mygets(e);
				if( e[0] == 'a' )
				{
					for(n = 1; n <= NTASK; n++)
					{
						wakeup(n);
					}
				}
				else
				{
					n = atoi(e);
					wakeup(n);
				}
				break;
			case 'a': mywait(x); break;
            default: break;  
       }
   }
}


main()
{
	myprintf("\nWelcome to the Dans Operating System: Multitasking System (MS-DOS)\n");
   	initialize();
   	tswitch();
 	myprintf("all dead, happy ending\n");
}


int scheduler()
{
    PROC *p;
	//grave_robber();
	//sand_man();
	if( running->next == running && running->status == READY)
		return 0;
    p = running->next;
	
    while (p->status != READY && p != running)
      p = p->next;

    if (p == running)
       running = &mainProc;
    else
       running = p;
}
