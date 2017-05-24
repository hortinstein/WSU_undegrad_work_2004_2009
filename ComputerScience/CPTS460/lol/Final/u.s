.globl begtext, begdata, begbss                      ! needed by linker

.globl _getcs
.globl _main0, _syscall, _exit
				
.text                                                ! these tell as:	
begtext:                                             ! text,data,bss segments
.data                                                ! are all the same.
begdata:
.bss
begbss:
.text           
	    
export auto_start                ! Need this to override bcc's crt0.o
auto_start:	

start:

        call _main0              ! NOTE: call main0() in crt0.c, which calls main()
	
	push  #0
        call _exit               ! exit(0) to die in MTX kernel
	 
_getcs:
        mov   ax, cs
        ret
	
_syscall:	
	int    80
	ret

