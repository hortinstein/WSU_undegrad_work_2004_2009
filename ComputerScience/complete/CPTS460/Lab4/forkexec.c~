copyImage(parent,child) ushort parent; ushort child;
{
	long i;
	for (i=0;i < 65536;i++)//64k to copy the whoe segment 
	{
		put_byte(get_byte(parent,i),child,i);
	}
}




/***********************************************************
  kfork() creates a child proc and returns the child pid.
  When scheduled to run, the child process resumes to body();
************************************************************/
int ufork()
{
  PROC *p;
  int  i, child;
  ushort  segment;
      
	/////////////////////////////////
  ushort curUserSeg; //this is where i store the current processes copy adress
	/////////////////////////////////
 
  /*** get a PROC for child process: ***/
  if ( (p = getproc()) == NULL){
       printf("no more proc\n");
       return(-1);
  }

  /* initialize the new proc and its stack */
  p->status = READY;
  p->ppid = running->pid;
  p->parent = running;
  p->pri  = 1;                 // all of the same priority 1


  // clear all SAVed registers on stack
  for (i=1; i<10; i++)
      p->kstack[SSIZE-i] = 0;
 
  // fill in resume address
  p->kstack[SSIZE-1] = (int)body;

  // save stack TOP address in PROC
  p->ksp = &(p->kstack[SSIZE - 9]);

  /* initialize the new proc and its stack */
  p->status = READY;
  p->pid = nproc;
  p->ppid = running->pid;
  p->parent = running;
  p->pri  = 1;                 // all of the same priority 1

  // clear all SAVed registers on stack
  for (i=1; i<10; i++)
      p->kstack[SSIZE-i] = running->kstack[SSIZE-i];
 
  // fill in resume address
  p->kstack[SSIZE-1] = running->kstack[SSIZE-1];//set equal to the current running processors resume address

  // save stack TOP address in PROC
  p->ksp = &(p->kstack[SSIZE - 9]);

  segment = (p->pid+1)*0x1000;//setting the segment based on the process id running
  printf("...creating a copy of u img for running process process %x at segment = %x\n",running->uss, segment );

copyImage(running->uss,segment);//copies the parents image to the child
  /***** Fill in U mode information in proc *********************
        12  11  10  9   8   7   6   5   4   3   2   1  |xxxxxxx
        DS  ES  di  si  bp  dx  cx  bx  ax  PC  CS  flag |
       seg seg  0   0   0   0   0   0   0   0   seg 0x0200
        | 
       usp
  **************************************************************/
 	
   for (i=1; i<=12; i++){
       put_word(0, segment, -2*i);//zeroing out the stack
   }
 
   put_word(0x0200,  segment, -2*1);   /* flag */  
   put_word(segment, segment, -2*2);   /* uCS */
   put_word(segment, segment, -2*11);  /* uES */
   put_word(segment, segment, -2*12);  /* uDS */
 
   p->usp = -2*12; 
   p->uss = segment;
  printf("...creating a copy of u img for running process process %d at segment = %x\n",p->pid, segment );

  enqueue(p);
  nproc++;

  // ADD CODE TO create a Umode image of the new process
  
  printf("Proc %d forked a child %d at segment=%d\n",
          running->pid, p->pid, segment);

  return(p->pid);
}
//
//This function changes the name of a process
//
void exec()
{
  	ushort segment, offset, a;
	int i = 0;	
	char name[128];   	
	segment = running->uss; offset = running->usp;//getting the running procs information
	offset = get_word(segment,offset + 28);//b's offset is 14 but since its a word 2 * 14  (getting the argument) 
	for (i = 0;i<128;i++){
		name[i] = get_word(segment,offset+i);
	}
	load(name,running->uss);

  for (i=1; i<=12; i++){
       put_word(0, segment, -2*i);//zeroing out the stack
   }
 
   put_word(0x0200,  segment, -2*1);   /* flag */  
   put_word(segment, segment, -2*2);   /* uCS */
   put_word(segment, segment, -2*11);  /* uES */
   put_word(segment, segment, -2*12);  /* uDS */
//   (b). "pretend" it had done  INT 80  from (virtual address) 0: 
//             (c). fill in uCS, uDS, uES in ustack
//             (d). execute from VA=0 ==> uPC=0, uFLAG=0x0200, 
//                                        all other registers = 0;
//             (e). fix proc.uSP to point at the current ustack TOP (-24)
	running->usp =-2*12;  
   //goUmode();
  
}

