/***********************************************
          ucode.c file
************************************************/
#include "type.h"
#include "hortinshelltype.h"

int getpid()
{
   return syscall(0,0,0);
}

int kmode()
{
   return syscall(3, 0, 0);
}    

int kswitch()
{
   return syscall(4,0,0);
}

int fork()
{  
   return syscall(5, 0, 0);
}

int exec(cmdline) char *cmdline;
{
   return syscall(6, cmdline, 0);
}

int wait(status) int *status;
{
   return syscall(20, status, 0);
}


int mkdir(name) char *name;
{
   return syscall(21, name, 0);
}

int rmdir(name) char *name;
{
   return syscall(22, name, 0);
}

int creat(name) char *name;
{
   return syscall(23, name, 0);
}

int rm(name) char *name;
{
   return syscall(24, name, 0);
}

int chdir(name) char *name;
{
    return syscall(26, name, 0);
}

int open(file, flag) char *file; int flag;
{
    return syscall(28, file, flag);
}

int close(fd) int fd;
{
    return syscall(29, fd);
}

long lseek(fd, offset, ww) int fd; long offset; int ww;
{
    return syscall(30, fd, (long)offset, ww);
}

int chmod(mode,file) int mode; char *file;
{
  return syscall(33, mode, file, 0);
}   

int chown(uid) int uid;
{
    return syscall(34, uid, 0);
}   

int read(fd, buf, nbytes) int fd, nbytes; char *buf;
{
    return syscall(35, fd, buf, nbytes);
}

int write(fd, buf, nbytes) int fd, nbytes; char *buf;
{
    return syscall(36, fd, buf, nbytes);
}


int stat(filename, sPtr) char *filename; struct stat *sPtr;
{   
   return syscall(38, filename, sPtr);
}

int getcwd(cwdname) char *cwdname;
{
    return syscall(39, cwdname, 0);
}

int pipe(pd) int *pd;
{
    return syscall(40, pd, 0);
}

int dup(fd) int fd;
{
    return syscall(41, fd, 0);
}

int dup2(fd,gd) int fd, gd;
{
    return syscall(42, fd, gd);
}

int kps()
{
   return syscall(43,0,0);
}


int getuid()
{
  return syscall(44, 0, 0);
}

int setuid(uid) int uid;
{
  return syscall(45, uid, 0);
}

int gettty(s) char *s;
{
  return syscall(46, s, 0);
}

int fixtty(s) char *s;
{
  return syscall(47, s, 0);
}


int fstat(fd, sptr) int fd; struct stat *sptr;
{
    return syscall(48, fd, sptr, 0);
}


int kill(sig, pid) int sig, pid;
{
    return syscall(50, sig, pid);
}

int signal(sig, catcher) ushort sig, catcher;
{
  return syscall(51, sig, catcher);
}

int sleep(t) ushort t;
{
  return syscall(52, t, 0);
}

int timer(t) ushort t;
{
  return syscall(53, t, 0);
}


int sync()
{
  return syscall(90,0,0);
}


int hitratio(requests, hits) int *requests, *hits;
{
  return syscall(96, requests, hits);
}

int exit(exitValue) int exitValue;
{
   syscall(99, exitValue, 0);
}

int pwd()
{
  char cwd[64];
  getcwd(cwd);
  printf("%s\n", cwd);
}

int getchar()
{
  return getc();
}
