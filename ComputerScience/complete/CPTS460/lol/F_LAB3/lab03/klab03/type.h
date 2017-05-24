/* Success/Failure Codes */
#define SUCCESS     1
#define FAIL       -1
#define EXIT        0

typedef unsigned short ushort;
typedef unsigned char uchar;

/*********** MTX Multitasking System ************/

#define NULL      0
#define NPROC     9
#define SSIZE  1024
#define NQUEUE NPROC    // at most NPROC ready queues

#define FREE      0     // proc statuc
#define READY     1
#define SLEEP     2
#define ZOMBIE    3

/* PROC Structure to manage the processes of the system */
typedef struct proc {
    struct proc * next;
    int  * ksp;          /* The saved sp; offset = 2 */

    int   uss, usp;  // at 4, 6

    int  pid;
    int  status;        /* FREE|READY|... Listed above */
    int  pri;      /* Scheduling priority */
    int  ppid;

    struct proc *parent;
    int event;          /* Event to sleep on */
    char   * deathCry;
    int  exitValue;     /* Exit code */

    char name[32];

    int kstack[SSIZE];  /* The stack of the PROC */
} PROC;

struct rqueue{
       int priority;    // 0, 1,...NQUEUE-1
       PROC * queue;     // PROC queue of this priority level
};

extern struct rqueue rqueue[];

extern PROC proc[NPROC], * running, * freeList, * sleepList;

