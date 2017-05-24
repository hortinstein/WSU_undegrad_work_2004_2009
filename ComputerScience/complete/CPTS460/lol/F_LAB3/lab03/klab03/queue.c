/***********************************************************************
 * getproc
 * Description:     Fetches a pointer to a free PROC structure in the
 *                  freeList linked list.
 * Params:
 * Return:          PROC * to a free PROC structure in the linked list.
 *                  NULL if there are no more free PROC structures.
 *
 **********************************************************************/
PROC * getproc()             /* get a pointer to a FREE proc */
{
    PROC * p = freeList;
    if ( p ) {
        freeList = p->next;
    }
    return p;
}

/***********************************************************************
 * putproc
 * Description:     Puts a PROC structure back on the freeList and sets
 *                  its status to FREE.
 * Params:          PROC * p - the pointer to the PROC being put back
 *                              into the freelist
 * Return:          int of the pid of the PROC that was put back
 *
 **********************************************************************/
int putproc(p) PROC * p;   /* return p to freelist */
{
    p->status = FREE;
    p->next = freeList;
    freeList = p;

    return p->pid;
}

/***********************************************************************
 * enqueue
 * Description:     Enter a new PROC * pointer into the rqueue array
 *                  according to priority.  Go to the index in the array
 *                  corresponding to the priority of the new PROC *
 *                  pointer and add it to its linked list.
 *
 *                  Note: rqueue is an array with each array element
 *                      containing a rqueue struct.  This struct has
 *                      a priority and a PROC * pointer for the linked
 *                      list to hold the queue.
 *
 * Params:          PROC * p - the PROC pointer to be inserted in the
 *                             rqueue[] array
 * Return:          int success/fail
 *
 **********************************************************************/
int enqueue(p) PROC * p;
{
    /* Let an iterator PROC * pointer point to the queue */
    PROC * i = rqueue[p->pri].queue;

    /* Set the next pointer to NULL by default */
    p->next = 0;

    /* Handle the case of an empty queue by automatically setting the
     * new queue head as the PROC * pointer to insert. */
    if ( i == 0 ) {
        rqueue[p->pri].queue = p;
        return SUCCESS;
    }

    /* Insert the new PROC * pointer into the end of the queue.  Using
     * the iterator PROC * pointer, we move along to the next PROC until
     * its next PROC is null.  When it is null (0), then we know we are
     * at the end.  So, we add the new PROC here. */
    while ( i->next != 0 ) {
        i = i->next;
    }

    i->next = p;

    return SUCCESS;
}

/***********************************************************************
 * dequeue
 * Description:
 * Params:
 * Return:
 *
 **********************************************************************/
PROC * dequeue( queue ) PROC ** queue;
{
    PROC * p = *queue;

    if (p) {
        *queue = p->next;
        return p;
    }

    return 0;
}

/***********************************************************************
 * printqueue
 * Description: Prints the contents of the rqueue[] ready queue.  It
 *              goes through each priority from 0 to NPROC and prints
 *              the corresponding queue in the rqueue struct.
 * Params:      None.
 * Return:      None.
 *
 **********************************************************************/
void printqueue()          /* print readyqueue */
{
    int i;
    PROC * p;

    printf("printqueue(): readyqueue: \n");

    for ( i = 0; i < NPROC; i++ ) {
        printf( "rqueue[%d]: ", rqueue[i].priority );

        p = rqueue[i].queue;
        while (p) {
            printf("P%d -> ",p->pid);
            p = p->next;
        }

        printf("NULL (End)\n");
    }

}
