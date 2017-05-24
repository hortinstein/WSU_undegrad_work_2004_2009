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
void wakeup( e ) int e;
{
    PROC * i = sleepList;

    while ( i != 0 ) {
        if ( i ->event  == e ) {
            i->status = READY;
            enqueue( i );
        }
        i = i->next;
    }
}
