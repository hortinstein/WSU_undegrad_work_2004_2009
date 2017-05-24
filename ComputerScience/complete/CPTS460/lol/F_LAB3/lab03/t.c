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

struct rqueue rqueue[NQUEUE];  // at most NPROC separate ready queues
PROC proc[NPROC];
PROC * running;
PROC * freeList;                /* The list of free PROCs */
PROC * sleepList;              /* The list of sleeping PROCs  */

int  procsize = sizeof(PROC);
int  nproc, color;

#include "io.c"           <==== printf(), etc
#include "word.c"       /*     <=== get/put_word() */
#include "queue.c"         /* <==== enqueue()/dequeue()/printqueue()/printlist() */
#include "wait.c"          /* <==== sleep()/wakeup()/wait()/exit() */

#include "int.c"   // <==== Replace with YOUR int.c file

int body();

int initialize()
{
    int i;
    PROC * p;

    ushort segment;

    printf("initialize(): Initializing MTX...\n");

    /* Initialize the array of PROCs.  Currently it is only up to 4
     * PROCS in the array.  Each will have its own PID and each next
     * pointer will be the next PROC in the array.  All priorities and
     * statuses will be initialized the same (1 and FREE). */
    for (i = 0; i < NPROC; i++) {
        proc[i].pid = i;                    /* PID = 0,1,2,3 */
        proc[i].status = FREE;
        proc[i].next=(PROC *)&proc[(i+1)];

        strcpy(proc[i].name, pname[i]);
    }

    freeList = &proc[0];                    /* All PROCs to freelist */

    /* Fix the last PROC in the array.  It cannot point to the next PROC
     * in the array because IT DOESN'T EXIST! */
    proc[NPROC-1].next = 0;

    for (i=0; i<NQUEUE; i++){    // initialize the scheduling queues
      rqueue[i].priority = i;
      rqueue[i].queue = 0;
    }
    sleepList = 0;

    /* Create P0 as the initial process.  getproc() grabs a PROC pointer
     * to a FREE PROC and uses it as P0. */
    printf("initialize(): Creating PROC 0 as the running process...\n");
    p = getproc();
    p->pri = 0;                        /* P0 has lowest priority */
    p->pid = 0;
    p->ppid = 0;
    running = p;                  /* Running pointer now points to P0 */

    nproc = 1;

    //************ P0 creates P1 with a Umode image ************

    printf("initialize(): P0 creates P1 with a Umode image\n");
    kfork();

    printf("initialize(): Initialization done!\n");

    return SUCCESS;
}

/***********************************************************************
 * kfork
 * Description:     Creates a CHILD process, puts it into the ready
 *                  queue, and returns its pid. Return -1 if kfork()
 *                  fails (due to no more FREE proc's).
 *
 *                  This implementation of kfork() also loads a user
 *                  image into a given segment.  Depending on the pid
 *                  of the newly created PROC, the segment will be
 *                  calculated according to the following:
 *
 *                      segment = (pid + 1) * 0x1000
 *
 *                  This is just the way MTX does it.
 *
 *                  It also initializes the umode stack image according
 *                  to the following:
 *
 *                      segment registers uCS,uDS,uES = segment
 *                      ax,bx,cx,dx,bp,si,di = 0
 *                      uPC =  0
 *                      uFlag=0x0200;
 *
 *                  Now, to remember the PROCs segment and stack top,
 *                  the information has to be stored in the PROC struct
 *                  itself:
 *
 *                      uSS = segment
 *                      uSP = Ustack top
 *
 * Params:
 * Return:          int as the pid of the newly created PROC
 *
 **********************************************************************/
int kfork()
{
    PROC *p;
    int  i = 0;
    int child;
    ushort  segment;

    /* Create a new PROC as a child process.  getproc() grabs a PROC
     * pointer to a FREE PROC and uses it as the new PROC.  The stack
     * image of the new PROC will be empty with the exception of the
     * body pointer and the ksp (save stack state) pointer. */
    printf("kfork(): Creating a new PROC...\n\r");
    p = getproc();

    if ( p == 0 ) {
        printf("kfork(): No more free PROCs!\n\r");
        return -1;
    }

    /* Set up the new PROCs initial settings */
    p->ppid = running->pid;
    p->status = READY;
    p->parent = running;
    p->pri  = 1;                 // all of the same priority 1
    strcpy( p->name, pname[p->pid] );

    /****************************************************************
    stack frame = -1    -2  -3  -4  -5  -6  -7  -8  -9
                 body  ax  bx  cx  dx  bp  si  di  flag
                                                    |
                                                   ksp
    ****************************************************************/

    /* Clear out the kstack frame of the new PROC */
    for (i=2; i<=9; i++)
        p->kstack[SSIZE - i] = 0;

    /* Set the body pointer to the location of body() function */
    p->kstack[SSIZE - 1] = (int)body;

    /* Set the ksp (remember the stack pointer location) so we can jump
     * back to the same location after tswitch(). */
    p->ksp = &p->kstack[SSIZE - 9];

    /* Set the segment as the (pid + 1) * 0x1000 to get to the place
     * MTX says to put the segment. */
    segment = (p->pid + 1) * 0x1000;

    /* Load the u1 image into the segment.  This is the default image.
     * */
    load("/bin/u1", segment);

    printf("kfork(): Creating a new user image segment for PROC %d at segment = %x\n",
            p->pid, segment );

    /***** Fill in U mode information in PROC *********************
        12  11  10  9   8   7   6   5   4   3   2   1  |xxxxxxx
        DS  ES  di  si  bp  dx  cx  bx  ax  PC  CS  flag |
       seg seg  0   0   0   0   0   0   0   0   seg 0x0200
        |
       usp
    **************************************************************/

    /* Fill the U mode stack with 0's */
    for (i=1; i<=12; i++) {
        put_word(0, segment, -2*i);
    }

    put_word(0x0200,  segment, -2*1);   /* flag */
    put_word(segment, segment, -2*2);   /* uCS */
    put_word(segment, segment, -2*11);  /* uES */
    put_word(segment, segment, -2*12);  /* uDS */

    p->usp = -2*12;
    p->uss = segment;

    /* Add new PROC to the readyqueue */
    enqueue(p);

    printf("kfork(): PROC %d forked a child PROC %d at segment = %x\n",
          running->pid, p->pid, segment);

    nproc++;

    return(p->pid);
}

int do_switch()
{
   printf("do_switch(): Switching PROCs...\n", running->pid);
   tswitch();
}

int do_wait( status ) int * status;
{
   printf("do_wait(): Sending PROC %d to sleep.\n", running->pid);
   return wait( status );
}

int do_kfork()
{
   int pid;
   pid = kfork();
   if (pid < 0)
       printf("do_kfork(): kfork() failed.\n");
}

void do_exit( v ) int v;
{
    exit( v );
}

/***********************************************************************
 * body
 * Description:     This is the default body of the stack image.  It
 *                  prompts the user to input a command and carries out
 *                  the command.
 *
 *                  Note: This is the body of the currently running
 *                        process stored on the kstack in the PROC
 *                        structure.  It will print out what the process
 *                        currently is and will also provide options for
 *                        playing the the processes.
 *
 *                  Note: Stack information is listed below.
 *
 * Params:          None
 * Return:          int success id
 *
 **********************************************************************/
int body()
{
    char c;

    while(1) {
        printf("=====================================================\n");
        printf("Running: PROC %d | Parent: PROC %d\n",
                running->pid, running->ppid);

        printf("=====================================================\n");
        printf("freeList: ");
        printList(freeList);
        printQ();
        printsleep();
        printf("=====================================================\n");

        printf("Input a command : [s|q|f|w|u] : ");
        c = getc();
        printf("%c\n", c);

        switch(c) {
            case  's' : do_switch();  break;
            case  'q' : do_exit(100); break;   /* no return */
            case  'f' : do_kfork();   break;
            case  'w' : do_wait(0);   break;
            case  'u' : goUmode();    break;

            default   :              break;
        }
    }
}

/***********************************************************************
 * int80h
 * Description:     This function saves the Umode registers in the
 *                  ustack.  It also saves the user stack pointer and
 *                  start segment in the PROC struct of the currently
 *                  running process.  It then changes the CPU stack
 *                  pointer to the end of the PROCs kstack[] by using
 *                  procsize global variable.  Then it calls kcinth().
 *
 *                  Note: This is defined in ts.s and kcinth() in int.c.
 *
 * Params:          None
 * Return:          None?
 *
 **********************************************************************/
int int80h();

/***********************************************************************
 * set_vec
 * Description:     This function sets the vector handler to whatever
 *                  address we want.
 *
 *                  Note: for this lab, it is the address of the
 *                      function int80h().
 *
 *                  First, the location in memory of where the BIOS will
 *                  jump to is calculated by taking the vector # and
 *                  plugging it into the formula:
 *
 *                      location = 4 * v
 *
 *                  The location in memory where the code data of our
 *                  handler will be stored is based on:
 *
 *                      location(segment) = (4 * v) + 2
 *
 *                  Now when int 80 is called from the BIOS, it will
 *                  load the values in (4 * v) and ((4*v)+2) into the
 *                  PC and CS register of the CPU.
 *
 *                  In this function, we put the address of the int80h()
 *                  function into (4 * v) and the kernel's code segment
 *                  into ((4*v)+2).  So when int 80 is called,
 *                  int80h() will be loaded on the kernel's code
 *                  segment.
 *
 * Params:          None
 * Return:          int success id
 *
 **********************************************************************/
int set_vec(vector, addr) ushort vector, addr;
{
    ushort location,cs;
    location = vector << 2;
    /* Segment 0 is the vector segment*/
    put_word(addr, 0, location);
    put_word(0x1000,0,location+2);

    return SUCCESS;
}

/***********************************************************************
 * main
 * Description:     The main function of the MTX kernel.  This
 *                  initializes the PROC structures 0 and 1.  It must
 *                  also set the interrupt vector 0x80 to point to
 *                  int80h(), which handles our interrupt.
 *
 * Params:          None
 * Return:          None
 *
 **********************************************************************/
main()
{
    color = 0x000B;
    set_vec(0x80, int80h);
    printf("\nWelcome to the MTX System\n");
    printf("=====================================================\n");
    initialize();
    printf("=====================================================\n");
    printf("main(): Switching from PROC 0 to PROC 1...\n");

    tswitch();
    printf("=====================================================\n");
    printf("main(): All PROCs are dead...\n");
    printf("main(): Exiting gracefully!\n");

    return EXIT;
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

