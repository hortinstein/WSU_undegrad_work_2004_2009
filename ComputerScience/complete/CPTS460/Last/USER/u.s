.globl begtext, begdata, begbss                      ! needed by linker

.globl _getcs, _getds
.globl _crt0, _syscall, _exit

.globl _int1,_int2,_int3,_int4,_int5,_int6,_int7
.globl _myint
.globl _iret
.globl _getbp
					
.text                                                ! these tell as:	
begtext:                                             ! text,data,bss segments
.data                                                ! are all the same.
begdata:
.bss
begbss:
.text           
	    

auto_start:	
export auto_start

start:

        call _crt0

        push  #0
        call  _exit

dead:   jmp   dead

_iret:	pop  ax
	pop ax
	pop ax
	iret

_getbp:
        push bp
	mov  bp,sp
	mov ax,bp
	pop bp
	ret
	

_int1:	int 1
	ret
_int2:	int 2
	ret
_int3:	int 3
	ret
_int4:	int 4
	ret
_int5:	int 5
	ret
_int6:	int 6
	ret
_int7:	int 7
	ret
	
_myint:
	push  bp
	mov   bp,sp

        mov   bx,4[bp]
	movb  ah,bl
	movb  al, #0xCD

	mov   fake,ax
	jmp fake
	
	pop   bp  	
	ret

fake:	.word	0
        pop  bp
	ret
	 
_getcs:
        mov   ax, cs
        ret
_getds: mov   ax, ds
        ret

		
_syscall:	
	int    80
	ret

