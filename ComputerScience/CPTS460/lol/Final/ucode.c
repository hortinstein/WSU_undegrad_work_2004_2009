#include "type.h"

int getc()
{
	int c;
	read(0, &c, 1);
	if (c==4)
		return 0;
   	return (c&0x7F);
}

int putc(c) int c;
{
   write(1, &c, 1);
   if (c=='\n')
      putc('\r');
}


int getpid()
{
   return syscall(0,0,0);
}

int fork()
{  
   return syscall(5, 0, 0);
}

int exec(file) char *file;
{
   return syscall(6, file, 0);
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
    return syscall(24, name[1], 0);
}

int chdir(name) char *name;
{
    return syscall(26, name, 0);
}

int open(file, mode) char *file; int mode;
{
    return syscall(28, file, mode);
}

int close(fd) int fd;
{
    return syscall(29, fd);
}

long lseek(fd, offset, ww) int fd; ulong offset;
{
    return syscall(30, fd, (ulong)offset);
}

int chmod(mode, filename) int mode; char *filename;
{
    return syscall(33, mode, filename);
}   

int chown(uid, filename) int uid; char *filename;
{
    return syscall(34, uid, filename);
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
    syscall(39, cwdname, 0);
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

int ps()
{
   return syscall(43,0,0);
}

int getuid()
{
  return syscall(44, 0);
}

int setuid(uid) int uid;
{
  return syscall(45, uid);
}

int gettty(s) char *s;
{
  return syscall(46, s, 0,0);
}

int settty(s) char *s;
{
  return syscall(47, s, 0,0);
}

int fstat(fd, sPtr) int fd; struct stat *sPtr;
{
    return syscall(48, fd, sPtr);
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
  return syscall(52, t);
}

int settimer(t) ushort t;
{
  return syscall(53, t);
}

int exit(ecode) ushort ecode;
{
   syscall(99, ecode, 0);
}
