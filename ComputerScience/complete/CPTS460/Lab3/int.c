char *pStatus[] = {"FREE   ","READY  ","RUNNING","ZOMBIE ", 0};
//This is a function that returns the pid to the user
//
//
void getpid()
{
	unsigned short segment = running->uss;//taken for kcinth method below to find the proper segment/offset 
	unsigned short offset = running->usp;

	put_word( running->pid, segment, offset + 16 );
}
//
//This function prints out all information about current running processes
//
void ps()
{
  PROC *p;

  printf("---------------------------\n");
  p = &proc[0];

  while (p < &proc[NPROC]){
    printf("%d   %s %s\n", p->pid, pStatus[p->status],p->name);
    p++;
  }
  printf("---------------------------\n");
  //printqueue();  

}
//
//This function changes the name of a process
//
void chname()
{
  	ushort segment, offset, a;
	int i = 0;	
	char name[32];   	
	segment = running->uss; offset = running->usp;//getting the running procs information
 	
	offset = get_word(segment,offset + 28);//b's offset is 14 but since its a word 2 * 14
	for (i = 0;i<32;i++){
		name[i] = get_word(segment,offset+i);
	}
	strcpy(running->name,name);//copy the name from the arument into the running name 
}
//
//brings the 
//
void kmode()
{
	body();//calls the body code of the kernel}
}
//
//switches the current running process
//
void kswitch()
{
	tswitch();//call the assembly code to switch processes
}
//
//
//
void kwait()
{
  	ushort segment, offset,stat_offset;
	int status,pid;//these are stored so we can put word to the user mode
	segment = running->uss; 
	offset = running->usp;//getting the running procs information
	
	stat_offset = get_word( segment, offset + 28 );//grabs the pointer from the (b) argument
	
	pid = wait( &status );//calling wait (status will return dead childs status)(pid gives the dead childs id)
	put_word( status, segment, stat_offset );//putting into the 
    	put_word( pid, segment, offset + 16 );//putting these into the return (ax) register

}
//
//
//
void kexit()
{
   ushort segment, offset, a;
   int exitv;
segment = running->uss; offset = running->usp;
   
    exitv = get_word( segment, offset + 2*14 );//getting location of (b) the offset for the pointer

    exit( exitv );
}
int kcinth()
{
   ushort segment, offset, a;
   segment = running->uss; offset = running->usp;
 
   a = get_word(segment, offset + 2*13);

   printf("\nkcinth: your syscall # = %d\n", a);
	switch(a){       
	/*************** FOR LAB #3 *********************************/
           case 0 : getpid();    break;
           case 1 : ps();        break;
           case 2 : chname();    break;
           case 3 : kmode();     break; 
           case 4 : kswitch();   break;
           case 5 : kwait();      break;
           case 6 : kexit();      break;
          
           /************** For LAB #4 **********************************/
//           case 7 : ufork();     break;
//           case 8 : exec();      break; 
           /************************************************************/

	}
}
