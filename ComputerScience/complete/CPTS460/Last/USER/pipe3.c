/********************** pipe3.c ****************************

                CORRECT usage of pipe:

 Parent : create pipe; fork a child to share the pipe
          Each process must be either a READER or a WRITER but NOT BOTH !!!

 parent : as pipe WRITER

 child  : as pipe READER

 ABNORMAL usage : broken pipe


                     DO THESE : 

1. Vary the value of N_READ to see what happens?__________________

2. Uncomment the line   // exit(1);  in child's code.
   WHAT HAPPENS and WHY?_________________________________________
 
**********************************************/

#define N 1024

int n, r, pd[2];

char *line = "this is a test line";
char buf[N];

// N_READ = number of bytes to read from pipe

#define N_READ 2

main(argc, argv) int argc; char *argv[ ];
{
  int i, pid, status;

  printf("proc%d pipe syscall\n", getpid());
  r = pipe(pd);
  printf("pipe descriptors = R=%d  W=%d\n", pd[0], pd[1]);

  pid = fork();
  
  if (pid){ // parent: as pipe WRITER
    close(pd[0]);

    for (i=0; i<1000; i++){  // try to write MANY MANY bytes to pipe
       n = write(pd[1], line, strlen(line));
       printf("i=%d  proc%d WROTE to pipe :%s\n", i, getpid(), line);
    }
  }

  else{    // child: as pipe READER
    close(pd[1]);

    //  exit(1);

    while(1){
       n = read(pd[0], buf, N_READ);
       if (n==0)
	  break;
       printf("proc%d READ : %s\n", getpid(), buf);
    }  
  }

}
