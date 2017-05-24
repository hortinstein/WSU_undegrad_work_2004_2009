/***********************************************************************
 * sleep
 * Description:     Puts the running PROC to SLEEP status and sets it
 *                  to wake up on an event.  sleep() is defined by the
 *                  Lab 2 assignment description:
 *
 *                  1. Records the event value in the proc structure
 *                  2. Changes its status to SLEEP
 *                  3. Gives up CPU
 *
 *                  A sleeping process will not run until it is awakened
 *                  by another process or an interrupt handler through
 *                  wakeup(event).
 *
 *                  Note: now the PROC is also added to a sleepList
 *                  queue.
 *
 * Params:          int e - event code to wake the PROC later
 * Return:          None
 *
 **********************************************************************/
void sleep( e ) int e;
{
    PROC * i = sleepList;

    running->event = e;
    running->status = SLEEP;
    running->next = 0;

    /* Handle the case of an empty queue by automatically setting the
     * new queue head as the PROC * pointer to insert. */
    if ( i == 0 ) {
        sleepList = running;
        tswitch();
    }

    /* Insert the new PROC * pointer into the end of the queue.  Using
     * the iterator PROC * pointer, we move along to the next PROC until
     * its next PROC is null.  When it is null (0), then we know we are
     * at the end.  So, we add the new PROC here. */
    while ( i->next != 0 ) {
        i = i->next;
    }
    i->next = running;

    tswitch();
}

/***********************************************************************
 * wakeup
 * Description:     Goes through each PROC in the sleepList queue and
 *                  wakes up any PROC that must wake on an event e.
 *
 * Params:          int e - event code to wake each PROC to
 * Return:          None
 *
 **********************************************************************/
int wakeup( e ) int e;
{
    PROC * c = sleepList;
    PROC * n = c->next;

    /* Handle the case where it is the head of sleepList. */
    if ( c->event == e ) {
        c->status = READY;
        sleepList = c->next;
        enqueue( c );
        return SUCCESS;
    }

    /* Handle everything else. */
    while ( n != 0 ) {
        if ( n->event == e ) {
            c->next = n->next;
            n->status = READY;
            enqueue( n );
            return SUCCESS;
        }
        c = c->next;
        n = n->next;
    }
}

/***********************************************************************
 * haschildren
 * Description:     Checks if the currently running PROC has any
 *                  forked on the proc[] array.  It checks each PROC
 *                  in the proc[] array.
 *
 *                  Note: This is inefficient.
 * Params:          None
 * Return:          int success id
 *
 **********************************************************************/
int haschildren()
{
    int i = 0;

    for ( i = 0; i < NPROC; i++ ) {
        if ( proc[i].status == READY && proc[i].ppid == running->pid ) {
            return SUCCESS;
        }
    }

    return FAIL;
}

/***********************************************************************
 * getzombie
 * Description:     Fetches a PROC with ZOMBIE status in the proc[]
 *                  array that is currently a child of the running PROC.
 *
 *                  Note: This is inefficient.
 * Params:          None
 * Return:          PROC * to the zombie PROC
 *                  NULL if there is no zombie PROC
 *
 **********************************************************************/
PROC * getzombie()
{
    int i = 0;

    for ( i = 0; i < NPROC; i++ ) {
        if ( proc[i].status == ZOMBIE && proc[i].ppid == running->pid ) {
            return &proc[i];
        }
    }

    return 0;
}

/***********************************************************************
 * wait
 * Description:     A task calls  pid = wait(int *status);  to wait for
 *                  a (ANY) child to die, where pid is the dead child's
 *                  pid and status is the child's exit value.
 *
 *                  If (found a ZOMBIE child){
 *                  copy child's exit value to *status;
 *                  free the dead child PROC;
 *                  return dead child's pid;
 *                  }
 *                  sleep(running);
 *
 * Params:          int status - status
 * Return:          None
 *
 **********************************************************************/
int wait( status ) int * status;
{
    PROC * p;

    if ( haschildren() != SUCCESS ) {
        printf("wait(): PROC %d has no children\n\r", running->pid);
        return -1;
    }

    printf("wait(): PROC %d waiting on children\n", running->pid);
    while (1) {
        p = getzombie();
        if ( p ) {
            printf("wait(): PROC %d found a zombie: PROC %d\n",
                    running->pid, p->pid);
            *status = p->exitValue;
            return putproc(p);
        }
        sleep(running);
    }
}

/***********************************************************************
 * get_p1
 * Description: Returns a PROC * pointer to PROC 1.
 * Params:      None.
 * Return:      PROC * to p1 or NULL
 *
 **********************************************************************/
PROC * get_p1()
{
    int i = 0;

    for ( i = 0; i < NPROC; i++ ) {
        if ( proc[i].status == READY && proc[i].pid == 1 ) {
            return &proc[i];
        }
    }

    return 0;
}

/***********************************************************************
 * exit
 * Description:     First, it must take all the children of the current
 *                  PROC and pass them as children of PROC 1.  This is
 *                  so no orphan PROCs are floating about.  It then
 *                  writes an exit value to the PROC and wakes
 *                  up its parent (ppid) to let it know that its child
 *                  has died.
 * Params:          int v - the exit value being given to the exit PROC
 * Return:          None
 *
 **********************************************************************/
void exit(v) int v;
{
    int i = 0;

    if ( running->pid == 1 && haschildren() == SUCCESS ) {
        printf("exit(): Cannot kill PROC 1.  It still has children!\n\r");
    }
    else {

        printf("---------------------------\n\r");
        running->status = ZOMBIE;

        printf("exit(): Giving all children of PROC %d to PROC 1 \n\r",
                running->pid);
        /* Giving all the children of running PROC to PROC 1. */
        for ( i = 0; i < NPROC; i++ ) {
            if ( proc[i].status == READY && proc[i].ppid == running->pid ) {
                proc[i].ppid = 1;
                /* GOTTA SET ITS PARENT POINTER TO P1 */
                proc[i].parent = get_p1();
                printf("    PROC %d now has ppid=1\n\r", proc[i].pid);
            }
        }

        printf("exit(): PROC %d exiting with exitValue = %d\n\r",
                running->pid, v);
        running->exitValue = v;

        /* Wakeup the parent of running PROC. */
        printf("exit(): Wake up parent PROC %d\n", running->parent->pid );
        wakeup( running->parent );

        printf("---------------------------\n\r");

        tswitch();
    }
}
