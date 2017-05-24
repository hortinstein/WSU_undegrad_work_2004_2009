/*************************************************************
  Change N value to find out pipe size of Linux __________
  
  Repeat for :                            MTX ___________

**************************************************************/

#define N 1000024

int n, r, pd[2];

char buf[N];

main(argc, argv) int argc; char *argv[ ];
{
  printf("%d pipe call\n", getpid());
  r = pipe(pd);
  printf("pipe descriptors = R=%d  W=%d\n", pd[0], pd[1]);

  printf("try to write %d bytes to pipe ENTER A KEY : ", N);
  r = getchar();
  printf("\nKEY=%c %x\n", r, r);

    n = write(pd[1], buf, N);

  printf("after write n=%d\n", n);

}
