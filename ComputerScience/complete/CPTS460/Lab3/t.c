/**************************************************************************
              MTX Base files for LAB#3 
     
1  ts.s   :   assembly file
2. type.h :   CONSTANTS and PROC type, also the rqueue type 
3. t.c    :   THIS FILE
4. int.c  :   kcinth() and system call functions YOU HAVE TO WRITE.

5. mtxlib :   library containing printf(), queue, sleep/wakeup/exit;
              get_word()/put_word(), etc.
              you may use these functions in mtxlib to get started.
              BUT MUST eventually REPLACE THESE BY YOUR OWN functions.


                       PRE-LAB WORK: 
1. Write YOUR own get_word(segment, offset) and put_word(w, segment,offset)
   fucntions. You will need them in this and later labs.

2. The kfork() fucntion, as provided, creates a new proc ready to run in K
   mode, but it cannot goUmode because the new proc does NOT have a Umode 
   image.
   MODIFY kfork() to allow any new proc to goUmode (to execute /u1).


3. Modify _syscall in u.s file to

                  _syscall:    int 0x80
                               ret

   Then, modify the MTX kernel code to make MTX work with this new syscall.
**************************************************************************/



#include "type.h"
#include "wait.c"   //      <==== sleep()/wakeup()/wait()/exit()
//#include "io.c"//my io.c file

/******** global kernel variables ****************************************/
 
struct rqueue rqueue[NQUEUE];  // at most NPROC separate ready queues 
PROC proc[NPROC], *running, *freeList, *sleepList;
int  procsize = sizeof(PROC);
int  nproc, color;

char *pname[]={"Sun", "Mercury", "Venus", "Earth",  "Mars", "Jupiter", 
               "Saturn", "Uranus", "Neptune" };


/********************************************************************
#include "io.c"           <==== printf(), etc
#include "queue.c"        <==== enqueue()/dequeue()/printqueue()/printlist()
#include "wait.c"         <==== sleep()/wakeup()/wait()/exit()
                          ALL ARE AVAILABLE in mtxlib BUT SHOULD USE YOUR OWN
*********************************************************************/
#include "wordops.c" //My get word and putword operations
#include "int.c"   // <==== Replace with YOUR int.c file

int body();

int initialize()
{
  int i; PROC *p;
  ushort segment;

  printf("MTX initializing ....\n");
   
  for (i=0; i < NPROC; i++){
      proc[i].pid = i; 
      proc[i].status = FREE;
      proc[i].next = (PROC *)&proc[(i+1)];

      strcpy(proc[i].name, pname[i]);
  }
  proc[NPROC-1].next = NULL;
  freeList = &proc[0];         // all PROC are FREE initially
   
  for (i=0; i<NQUEUE; i++){    // initialize the scheduling queues
      rqueue[i].priority = i;
      rqueue[i].queue = 0;
  }
  sleepList = 0;

  // create P0
  p = getproc();              // get a FREE PROC

  p->status = READY;
  p->pri = 0;                /* lowest priority  0 */
  p->pid = 0;                /* process 0 or P0 */
  running = p;
  p->ppid = running->pid;    /* P0's parent is P0 */
  nproc = 1;

  //************ P0 creates P1 with a Umode image ************

  printf("P0 creates P1 with a Umode image\n");
  p = getproc();

  /* initialize the new proc and its stack */
  p->status = READY;
  p->pid = 1;
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

  segment = (p->pid+1)*0x1000;//setting the segment based on the process id running

  load("/bin/u1", segment);//loading the default memory into the segment
  printf("...creating new u img for process %d at segment = %x\n",p->pid, segment );
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

   enqueue(p);
   nproc++;


  printf("initialization complete\n"); 
}

/***********************************************************
  kfork() creates a child proc and returns the child pid.
  When scheduled to run, the child process resumes to body();
************************************************************/
int kfork()
{
  PROC *p;
  int  i, child;
  ushort  segment;

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
      p->kstack[SSIZE-i] = 0;
 
  // fill in resume address
  p->kstack[SSIZE-1] = (int)body;

  // save stack TOP address in PROC
  p->ksp = &(p->kstack[SSIZE - 9]);

  segment = (p->pid+1)*0x1000;//setting the segment based on the process id running

  load("/bin/u1", segment);//loading the default memory into the segment
  printf("...creating new u img for process %d at segment = %x\n",p->pid, segment );
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

  enqueue(p);
  nproc++;

  // ADD CODE TO create a Umode image of the new process
  
  printf("Proc %d forked a child %d at segment=%d\n",
          running->pid, p->pid, segment);

  return(p->pid);
}

int do_switch()
{ 
   printf("P%d switch process\n", running->pid);
   tswitch();
}

int do_kfork()
{
   int new;
   new = kfork();
   if (new < 0)
       printf("kfork failed\n");
   else
       printf("P%d return from kfork() : child = %d\n",
               running->pid, new);
}
int do_wait( status ) int * status;
{
   return wait( status );
}
int body()
{
  char c;

  while(1){
    printf("------------------------------------------\n"); 
    printf("I am process P%d    My parent=%d\n", running->pid, running->ppid);
    
    printf("******************************************\n");
    printf("freeList   = "); printList(freeList);
    printQ();
    printsleep();
    printf("******************************************\n");

    printf("input a command : [s|q|f|w|u] : ");
    c = getc();   
    printf("%c\n", c);

    switch(c){
      case  's' : do_switch();  break;
      case  'q' : do_exit(100); break;   /* no return */
      case  'f' : do_kfork();   break;
      case  'w' : do_wait(0);   break;

      case  'u' : goUmode();    break;

      default   :              break;  
    }
  }
}

int int80h();

int set_vec(vector, addr) ushort vector, addr;
{
    ushort location,cs;
    location = vector << 2;
    put_word(addr, 0, location);
    put_word(0x1000,0,location+2);
}

//*************** main() ***************
main()
{
   color = 0x000C;
   printf("\nWelcome to the MTX Operating System\n");
     initialize();
 
     set_vec(80, int80h);

   printf("P0 forks P1\n");
     kfork();
   printf("P0 switches to P1\n");
     tswitch();
   printf("P0 resumes: all dead, happy ending!\n");
}

//******** scheduler *******************

int scheduler()
{ 
  PROC *p;
  int i;

  if (running->status == READY)
      enqueue(running);

  for (i=NQUEUE-1; i>=0; i--){
       running = dequeue(&rqueue[i].queue);
       if (running)
          break;
  }
}


