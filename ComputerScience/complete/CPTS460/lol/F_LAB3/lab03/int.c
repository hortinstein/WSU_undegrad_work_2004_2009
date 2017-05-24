/***********************************************************************
 * getpid()
 * Description:     Get the pid of the currently running process and
 *                  store it to the location of the ax register in the
 *                  user image user stack.  The ax register is the
 *                  return register.
 *
 * Params:          None
 * Return:          None
 *
 **********************************************************************/
void getpid()
{
    ushort segment = running->uss;
    ushort offset = running->usp;

    put_word( running->pid, segment, offset + 2*8 );
}

/***********************************************************************
 * ps
 * Description:     Lists the current proc[] information (pid, status).
 *                  It also prints the current readyqueue.
 * Params:          None
 * Return:          None
 *
 **********************************************************************/
void ps()
{
    int i = 0;

    printf("\nPROC    Status     Name\n");
    for ( i = 0; i < NPROC; i++ ) {
        printf(" %d     %s     %s\n", proc[i].pid, pStatus[proc[i].status], proc[i].name);
    }
}

/***********************************************************************
 * chname
 * Description:     This function changes the name of the PROC in the
 *                  PROCs name field by accessing the argument passed
 *                  by syscall().  This is in the b location in memory
 *                  at (offset + 2*14).  The b argument is actually an
 *                  offset on the user segment stack.  When we go to
 *                  this offset, it will have our characters of the b
 *                  argument.
 *
 *                  To get the characters, we must copy (word for word)
 *                  the characters.  We do this by copying the word at
 *                  the offset and incrementing the offset.  Then we
 *                  repeat.
 *
 * Params:          None
 * Return:          None
 *
 **********************************************************************/
void chname()
{
    ushort segment = running->uss;
    ushort offset = running->usp;

    char name[NAMELEN];
    ushort name_offset;         /* Offset to the new name buffer on the
                                    ustack */

    int i = 0;

    /* syscall()'s b argument is a pointer to a string.  When we get it
     * here in kernel mode, it is an OFFSET in relation to the SEGMENT.
     */
    name_offset = get_word( segment, offset + 2*14 );

    /* So, we must get the data at this offset in the user segment.  We
     * get a word (char) in the offset specified by the name_offset,
     * then increment it by 1 to get the next char.  Since we know that
     * the string in the user image stack is only 32 chars long, we just
     * copy the whole 32 words (chars) in a row.*/
    for ( i = 0; i < NAMELEN; i++ ) {
        name[i] = get_word( segment, name_offset + i );
    }

    /* Now we want to change the name in the PROC struct of currently
     * running process. */
    strcpy( running->name, name );
}

/***********************************************************************
 * kmode
 * Description:     Run body().
 *
 * Params:          None
 * Return:          None
 *
 **********************************************************************/
void kmode()
{
    body();
}

/***********************************************************************
 * kswitch()
 * Description:     Run tswitch().
 *
 * Params:          None
 * Return:          None
 *
 **********************************************************************/
void kswitch()
{
    tswitch();
}

/***********************************************************************
 * kwait()
 * Description:     Sends the currently running process to sleep to wait
 *                  on an event.  The status of the event is stored in
 *                  a pointer passed by syscall().  This pointer is
 *                  stored in the b argument in syscall().  The pointer
 *                  is an offset in the user image stack from the user
 *                  image segment.
 *
 *                  After the wait() is called, the return value from
 *                  wait() is stored in the ax register.  (ax is the
 *                  return register).  This is so syscall() can return
 *                  with the value.
 *
 * Params:          None
 * Return:          None
 *
 **********************************************************************/
void kwait()
{
    ushort segment = running->uss;
    ushort offset = running->usp;
    ushort status_offset;
    /* Store locally so we can write it into the user image using
     * put_word() later. */
    int status;
    int pid;

    /* Grab the pointer (offset in user image stack from segment) to
     * the status argument from syscall().  (offset+(2*14)) is the
     * location from the segment in the user image. */
    status_offset = get_word( segment, offset + 2*14 );

    /* Use the local variables to call wait() */
    pid = wait( &status );

    /* Write the local variables to user stack as the new status value
     * and return value for wait. */
    put_word( status, segment, status_offset );
    put_word( pid, segment, offset + 2*8 );
}

/***********************************************************************
 * kexit()
 * Description:     Call exit based on the exit value stored in the user
 *                  image stack.
 *
 * Params:          None
 * Return:          None
 *
 **********************************************************************/
void kexit()
{
    ushort segment = running->uss;
    ushort offset = running->usp;

    char exit_value;

    /* Grab the exit value argument from syscall().  (offset+(2*14)) is
     * the location of b from the segment in the user image. */
    exit_value = get_word( segment, offset + 2*14 );

    exit( exit_value );
}

/***********************************************************************
 * invalid()
 * Description:     Prompts an error message.
 *
 * Params:          None
 * Return:          None
 *
 **********************************************************************/
void invalid()
{
    printf("kcinth(): Invalid syscall!\n");
}

int kcinth()
{
    ushort segment = running->uss;
    ushort offset = running->usp;

    /* Get the argument a from syscall(a,b,c,d) in user mode.  We must
     * access the user mode stack which is stored in the PROC struct.
     * We then apply the offset corresponding to the spot on the stack
     * the syscall() arguments are stored. */

    /* LOW                                                                 High
     * | uds,ues,udi,usi,ubp,udx,ucx,ubx,uax |upc,ucs,uflag|retPC, a, b, c, d |...
     *    0   1   2   3   4   5   6   7   8    9   10  11    12    13 14 15 16
     */
   switch(get_word(segment, offset + 2*13)){
           case 0 : getpid();   break;
           case 1 : ps();       break;
           case 2 : chname();   break;
           case 3 : kmode();    break;
           case 4 : kswitch();  break;
           case 5 : kwait();     break;
           case 6 : kexit();     break;

           default: invalid();  break;
    }
}
