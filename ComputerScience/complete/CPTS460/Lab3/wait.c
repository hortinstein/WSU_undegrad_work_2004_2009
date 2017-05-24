
sleep(event) int event;
{
	PROC *curr;
	running->event = event;      //Record event in PROC
	running->status = SLEEP;     // mark SLEEP
	
	// For fairness, put running into a FIFO sleepList so that they will wakeup in order
	if (sleepList==0)//if the ready queue is empty
	{
    	sleepList = running;
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
				aids->next = freeList;//adding this process to the head of the free list
				freeList = aids;
				status = &proc[i].exitValue;//copy child's exit value to *status;
				return (proc[i].pid);//returning dead child's PID
			}		
		}	
		
		sleep(running->pid);    // sleep at its own &PROC
	}
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

int exit(v) int v;
{
	int i;
	if (running->pid == 1 && rqueue != 0)
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



