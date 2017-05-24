/************ main.c file **********************************/
#define NPROC     4        
#define SSIZE  1024       // per proc kstack size 

#define FREE      0       // proc status 
#define READY     1      
#define RUNNING   2
#define ZOMBIE    3
#define SLEEP	  4
typedef struct proc{
    struct proc *next;   
    int  *ksp;            // saved sp; offset = 2

    int  pid;
    int  ppid;
    int  priority;        // scheduling priority
    int  status;          // FREE|READY|.... 
    int  exitValue;       // exit code  
	int	 event;
    int  kstack[SSIZE];    // per proc kmode stack 
}PROC;

PROC proc[NPROC], *running, *freelist, *readyqueue, *sleeplist=0;
int  procsize = sizeof(PROC);

int body();
PROC *getproc();
PROC *dequeue();

#include "io.c"    // YOUR gets, printf functions
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//2. MAIN WORK OF LAB #2
//Modify the MTX system to include the following:
//
//	1. sleep(event)/wakeup(event):
//	   As shown in Notes #4
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
sleep(event) int event;
{
	PROC *curr;
	running->event = event;      //Record event in PROC
	running->status = SLEEP;     // mark SLEEP
	
	// For fairness, put running into a FIFO sleepList so that they will wakeup in order
	if (sleeplist==0)//if the ready queue is empty
	{
    	sleeplist = running;
	}  	
	else{
		curr = sleeplist;
    	while (curr->next!=0)//while there are still elements in the sleepqueue
		{
			curr = curr->next;
			if (curr == running)//if the next process is running break 
				break;		
		}
		curr->next = running;
		running->next = 0;
				
  	}
	tswitch();                   // not in readyQueue anymore
} 

wakeup(event) int event;
{
	PROC *p = sleepList;
	PROC *prev = running;	
	while(p){
		if (p->event == event)//for every task p SLEEPing on this event 	
		{
			// remove p from sleepList if you implement a sleepList
			p->status = READY;        // make it READY
			prev->next = p->next;	  // link the list		
			enqueue(p);                // enter it into a ready queue (by its pri)
		}
		p = p->next;
	}
	
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//	2. pid = wait(&status):
//	   The logic of wait() is explained in Notes #4.
//	   Implement it in YOUR MTX.
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

// Wait for a child task to die:
//     A task calls  pid = wait(int *status);  to wait for A (ANY) child to die, 
//     where pid is the dead child's pid and status is the child's exit value.
int wait(status) int *status;
{
	int i;//interator for the processes	
	PROC* aids;	
	for (i=0;i<(NPROC+1);i++)//going through the processes and finding if it even has a child
	{
		if (i == NPROC)//if the loop hasnt broken it will hop out here because there have been no discovered children
		{
			printf("...running proc (%d) has no children\n",running->pid);
			return -1;
		}
		if (proc[i].ppid == running->pid)//checks them against running pid
		{
			break;
		}		
	}	
	while(1)//loop untill a child dies
	{
		for (i=0;i<(NPROC);i++)//going through the processes and finding zombie childs
		{
			if (proc[i].ppid == running->pid && proc[i].status == ZOMBIE)//checks them against running pid and if they are a (un)dead child
			{
				printf("...proc %d was found to be a shamblor and killed\n",proc[i].pid);				
				proc[i].status == FREE;//free the dead child PROC;
				aids = &proc[i];
				aids->next = freelist;//adding this process to the head of the free list
				freelist = aids;
				status = &proc[i].exitValue;//copy child's exit value to *status;
				return (proc[i].pid);//returning dead child's PID
			}		
		}	
		
		sleep(running->pid);    // sleep at its own &PROC
	}
}




//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//	(2). Implement a    pid = kfork();
//	     function, which creates a CHILD process, put it into the ready queue
//	     and return its pid. Return -1 if kfork() fails (due to no more FREE
//	     proc's). Use YOUR kfork() to create P1. 
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
int kfork()
{	
	PROC* temp;
	int i;
	if (freelist == '\0')//if the free list has no room in it
	{
		printf("...FORK FAILED: no more free processes");
		return (1);//return a faulty exit status
	}
	temp = getproc();//grab the off free list (getproc)
	temp->ppid = running->pid;//initialize the new processes parent by refrencing the running pointer	
	temp->status = READY;//setting the new process status to ready
    for (i=2; i<=9; i++)
	{
       temp->kstack[SSIZE - i] = 0;
	}    
	temp->kstack[SSIZE - 1] = (int)body;//initializing the stack size
    temp->ksp = &temp->kstack[SSIZE - 9];
	temp->next = 0;  	
	enqueue(temp);//puts the proc into ready queue
	return temp->pid;	
}	
int initialize()
{
  int i;
  PROC *p;

  printf("initialize ....\n");

  for (i = 0; i < NPROC; i++){
    proc[i].pid = i;                        // pid = 0,1,2,3 */    
      proc[i].status = FREE;
      proc[i].priority = 1;                 // all have priority = 1        
      proc[i].next=(PROC *)&proc[(i+1)];       
  }
  freelist = &proc[0];                      // all proc's in freelist
  proc[NPROC-1].next = 0;

  readyqueue = 0;                          // readyqueue = empty

  // create P0
  printf("create P0 as running\n");
  p = getproc();
  p->status = RUNNING;
  p->priority = 0;                        // P0 has lowest priority
  running = p;

  printf("create P1, put into readyqueue\n");
  //p = getproc();
  //p->status = READY;
  //p->priority = 1;

  /****************************************************************
   stack frame = -1    -2  -3  -4  -5  -6  -7  -8  -9
                 body  ax  bx  cx  dx  bp  si  di  flag
                                                    |
                                                   ksp
  ****************************************************************/
  // for (i=2; i<=9; i++)
  //     p->kstack[SSIZE - i] = 0;
  // p->kstack[SSIZE - 1] = (int)body;
  // p->ksp = &p->kstack[SSIZE - 9];
	kfork();
   //enqueue(p);
   printqueue();

   prints("initialization done\n"); 
}

int body()
{  
   char c;
   while(1){
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//	(4). Add a 'f' command to body(), which creates a CHILD process, puts it
//	     into ready queue and return its pid (or -1 if failure).
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
	int *gasp;
     printf("I am Proc%d : Input a char [a|p|s|q|f] : ", running->pid); 
     c=getc();
	putc(c);//prints out so i can see the kernel command entered     
	printf("\n");

     switch(c){
		case 'a': printall();  break;
        case 'p': ps();        break;
        case 's': tswitch();	printall(); printf("\n");   break;
        case 'q': kexit(1);    break;
		case 'f': kfork(); 		printall(); printf("\n"); 	break;
		case 'w': wait(gasp);  break;        
		default :              break;  
     }
   }
}


main()
{
   printf("\nWelcome to the 460 MTX System\n");
   initialize();

   printf("P0 switch to P1\n");
     tswitch();
   printf("main resumes: happy ending\n");
}

int scheduler()
{
    PROC *p;

    if (running->pid>0){
       if (running->status == RUNNING){
           running->status = READY;
           enqueue(running);
       }
    }
    running = dequeue();
    
}


// utility functions

PROC *getproc()             // get a pointer to a FREE proc
{
  PROC *p = freelist;
  if (p){
    freelist = p->next;
  }
  return p;
}

int putproc(p) PROC *p;   // return p to freelist
{
  p->status = FREE;
  p->next = freelist;
  freelist = p;

}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//	(3). Finish the enqueue() function, which enters a proc (pointer) into 
//	     readyqueue by priority (FIFO if same priority).
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

int enqueue(p) PROC *p;   // enter p into readyqueue
{
	PROC *curr,*prev;
	if (readyqueue==0)//if the ready queue is empty
	{
    	readyqueue = p;
	}  	
	else{
    	//enqueues by priority
		prev = running;//setting the prev pricess to running
		curr = readyqueue;//setting current to head of the ready list to begin iteration
		while (curr->priority >= p->priority)
		{
			prev = curr;//iterate through the process list
			curr = curr->next;//iterate through the process list
			if (curr == running)//if the next process is running break 
				break;
		}
			p->next  = curr;//inserting p into its proper place
			prev->next = p;
  	}
  }


PROC *dequeue()         // remove and return FIRST proc from readyqueue
{
  PROC *p = readyqueue;

  if (p){
    readyqueue = p->next;
    p->status = RUNNING;
    return p;
  }
  return &proc[0];        // if readyqueue empty => return P0
}

int printqueue()          // print readyqueue 
{
	PROC *p = readyqueue;	
	printf("readyqueue = ");
  	while (p){
    	printf("%d-> ",p->pid);
    	p = p->next;
  	}
  	printf("NULL\n");
}
int printall()          // print readyqueue 
{
	PROC *p = readyqueue;	
	//PRinting the running proc
	printf("...proc %d is running\n",running->pid);	
	//Printing the readyqueue
  		
	printf("...readyqueue = ");
  	while (p){
    	printf("%d-> ",p->pid);
    	p = p->next;
  	}
  	printf("NULL\n");
	//Printing the Freelist	
	p = freelist;
  	printf("...freelist = ");
  	while (p){
    	printf("%d-> ",p->pid);
    	p = p->next;
  	}
  	printf("NULL\n");
	p = sleeplist;
  	printf("...sleeplist = ");
	while (p){
    	printf("%d-> ",p->pid);
    	p = p->next;
  	}
  	printf("NULL\n");
}	

char *pStatus[] = {"FREE   ","READY  ","RUNNING","ZOMBIE ", 0};

int ps()                 // print all proc pid and status
{
  PROC *p;

  printf("---------------------------\n");
  p = &proc[0];

  while (p < &proc[NPROC]){
    printf("%d   %s\n", p->pid, pStatus[p->status]);
    p++;
  }
  printf("---------------------------\n");
  printqueue();  
}

char *gasp[NPROC]={
     "Oh! You are killing me .......\n",
     "Oh! I am dying ...............\n", 
     "Oh! I am a goner .............\n", 
     "Bye! Bye! World...............\n",      
};

int grave(){
  printf("*****************************************\n"); 
  printf("Proc%d %c %s", running->pid, 7, gasp[(running->pid) % NPROC]);
  printf("*****************************************\n");
  running->status = ZOMBIE;

  tswitch();   /* journey of no return */        
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//3. kexit(value) int value:
//   A process calls kexit(value) to die, in which it
//     . become a ZOMBIE; 
//     . print last gasp and records the gasp string (pointer) as "exitValue" 
//       in PROC;
//     . give away all children to Task1;
//     . wakeup its parent;
//     . finally, tswitch() to give up CPU.
// 
//   Also, implement these into kexit():
//     Process P1 cannot die if there are other READY tasks.
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

int kexit(v) int v;
{
	int i;
	if (running->pid == 1 && readyqueue != 0)
	{	
		return -1;
	}  
	for (i=0;i<(NPROC);i++)//going through the processes and finding if it even has a child
	{
		if (proc[i].ppid == running->pid)//assigning all children to pid1
		{
			//printf("...assigning orphaned proc %d to proc 1\n",proc[i].ppid);
			proc[i].ppid =1;		
		}		
	}
	printf("Proc%d in kexit(): exitValue=%d\n", running->pid, v);
	running->exitValue = v; 
	wakeup(running->ppid);
  	grave();

}



