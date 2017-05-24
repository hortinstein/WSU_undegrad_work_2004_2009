/***********************************************************
    Run pipe1.c under both Linux and MTX

    EXPLAIN WHAT HAPPENS & WHY?______________

***********************************************************/

#define N 80

int n, r, pd[2];

char buf[N];

main()
{
  printf("proc%d : pipe syscall\n", getpid());
  r = pipe(pd);
  printf("pipe descriptors : READ=%d  WRITE=%d\n", pd[0], pd[1]);

  printf("proc%d : try to read 1 byte from pipe ENTER A KEY : ", getpid());
  r = getchar();
  printf("\nKEY=%c %x\n", r, r);

    n = read(pd[0], buf, 1);  // read ONE byte !!!!

  printf("read n=%d bytes\n", n);
}
