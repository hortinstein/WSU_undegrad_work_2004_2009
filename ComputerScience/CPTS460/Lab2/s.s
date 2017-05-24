.globl begtext, begdata, begbss                      ! needed by linker

.globl _main, _getc, _putc
.globl _tswitch, _running, _scheduler
.globl _proc, _procsize
	 
.text                                                ! these tell as:	
begtext:                                             ! text,data,bss segments
.data                                                ! are all the same.
begdata:
.bss
begbss:
.text           

start:
        mov     ax, cs                   ! establish segments 
        mov     ds, ax                   ! Let DS,SS,ES = CS=0x1000.
        mov     ss, ax                   
        mov     es, ax

        mov     sp, #_proc	 
        add     sp, _procsize           ! sp->HI end of proc[0]
	
        call _main                      ! call main[] in C

dead:	jmp dead                        ! loop if main() ever returns

	
_tswitch:
SAVE:	push ax
        push bx
	push cx
	push dx
	push bp
	push si
	push di
        pushf
	mov   bx, _running
	mov   2[bx], sp

FIND:	call _scheduler

RESUME: mov   bx, _running
	mov   sp, 2[bx]
	popf
	pop  di
	pop  si
	pop  bp
	pop  dx
	pop  cx
	pop  bx
	pop  ax
	ret


_getc:
        xorb   ah,ah 
        int    0x16  
        ret 

_putc:           
        push   bp
        mov    bp,sp
        movb   al,4[bp]
        movb   ah,#14  
        mov    bx,#0x000B 
        int    0x10    
        pop    bp
        ret
