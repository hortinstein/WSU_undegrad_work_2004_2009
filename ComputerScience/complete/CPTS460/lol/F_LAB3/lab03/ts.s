                BOOTSEG = 0x1000
.globl begtext, begdata, begbss                      !! needed by linker

!               IMPORTS and EXPORTS
.globl _resetVideo,_getc,_putc,_diskr,_setes,_inces 
.globl _main,_prints                                 
.globl _tswitch,_running,_scheduler

.globl _int80h,_kcinth
.globl _goUmode
.globl _get_byte,_put_byte
.globl _proc, _procsize
.globl _color

.text                                                !! these tell as:	
begtext:                                             !! text,data,bss segments
.data                                                !! are all the same.
begdata:
.bss
begbss:
.text                                                

        mov     ax,cs                   ! establish segments 
        mov     ds,ax                   ! we know ES,CS=0x1000. Let DS=CS  
        mov     ss,ax                   ! SS = CS ===> all point to 0x1000
        mov     es,ax

        mov     sp,#_proc               ! SP -> proc[0].kstack HIGH end
        add     sp,_procsize

        call _main                      ! call main[] in C

! if ever return, just hang     
        mov   ax, #msg
        push  ax
        call  _prints
dead:   jmp   dead
msg:    .asciz "BACK TO ASSEMBLY AND HANG\n\r"    
	
!*************************************************************
!     KCW  added functions for MT system
!************************************************************
_tswitch:
          push   ax
          push   bx
          push   cx
          push   dx
          push   bp
          push   si
          push   di
	  pushf
	  mov	 bx, _running
 	  mov	 2[bx], sp

find:     call	 _scheduler

resume:	  mov	 bx, _running
	  mov	 sp, 2[bx]
	  popf
	  pop    di
          pop    si
          pop    bp
          pop    dx
          pop    cx
          pop    bx
          pop    ax
          ret

!These offsets are defined in struct proc
USS =   4
USP =   6

_int80h:
        push ax                 ! save all Umode registers in ustack
        push bx
        push cx
        push dx
        push bp
        push si
        push di
        push es
        push ds

! ustack contains : flag,uCS,uPC, ax,bx,cx,dx,bp,si,di,ues,uds
        push cs
        pop  ds                 ! KDS now

	mov si,_running  	! ready to access proc
        mov USS[si],ss          ! save uSS  in proc.USS
        mov USP[si],sp          ! save uSP  in proc.USP

! Change ES,SS to kernel segment
        mov  di,ds              ! stupid !!        
        mov  es,di              ! CS=DS=SS=ES in Kmode
        mov  ss,di

! set sp to HI end of running's kstack[]
	mov  sp,_running        ! proc's kstack [2 KB]
        add  sp,_procsize       ! HI end of PROC

        call  _kcinth

        jmp   _goUmode
  
_goUmode:
        cli
	mov bx,_running 	! bx -> proc
        mov cx,USS[bx]
        mov ss,cx               ! restore uSS
        mov sp,USP[bx]          ! restore uSP
  
	pop ds
	pop es
	pop di
        pop si
        pop bp
        pop dx
        pop cx
        pop bx
        pop ax  
        iret
	
        !--------------------------------
        ! resetVideo[] : clear screen, home cursor
        !--------------------------------
_resetVideo:	
        mov     ax, #0x0012             ! 640x480 color
        int     0x10                    ! call BIOS to do it
        mov     ax, #0x0200             ! Home the cursor
        xor     bx, bx
        xor     dx, dx
        int     0x10                    ! call BIOS to home cursor 
        ret 

       !---------------------------------------
       ! int diskr[cyl, head, sector, buf] 
       !            4     6     8     10
       !---------------------------------------
_diskr:                             
        push  bp
	mov   bp,sp
	
        movb  dl, #0x00        ! drive 0=fd0
        movb  dh, 6[bp]        ! head
        movb  cl, 8[bp]        ! sector
        incb  cl               ! inc sector by 1 to suit BIOS
        movb  ch, 4[bp]        ! cyl
        mov   ax, #0x0202      ! READ 2 sectors 
        mov   bx, 10[bp]       ! put buf value in BX ==> addr=[ES,BX]
        int  0x13              ! call BIOS to read the block 
        jb   error             ! to error if CarryBit is on [read failed]

	mov   sp,bp
	pop   bp
	ret

        !---------------------------------------------
        !  char getc[]   function: returns a char
        !---------------------------------------------
_getc:
        xorb   ah,ah           ! clear ah
        int    0x16            ! call BIOS to get a char in AX
        ret 

        !----------------------------------------------
        ! void putc[char c]  function: print a char
        !----------------------------------------------
_putc:           
        push   bp
	mov    bp,sp
	
        movb   al,4[bp]        ! get the char into aL
        movb   ah,#14          ! aH = 14
 
        mov    bx,_color       ! bL = color B Cyan C Red  
        int    0x10            ! call BIOS to display the char

        mov    sp,bp
	pop    bp
	ret
	        
        
_setes:  push  bp
	 mov   bp,sp
	
         mov   ax,4[bp]        
         mov   es,ax

	 mov   sp,bp
	 pop   bp
	 ret

_inces:                        ! inces[] inc ES by 0x40, or 1K
         mov   ax,es
         add   ax,#0x40
         mov   es,ax
         ret

        !------------------------------
        !       error & reboot
        !------------------------------
error:
        mov  bx, #bad
        push bx
        call _prints
        
        int  0x19                       ! reboot
bad:    .asciz  "Error!"


!*===========================================================================*
!*				get_byte				     *
!*===========================================================================*
! This routine is used to fetch a byte from anywhere in memory.
! The call is:
!     c = get_byte[segment, offset]
! where
!     'segment' is the value to put in es
!     'offset'  is the offset from the es value
_get_byte:
	push bp			! save bp
	mov bp,sp		! we need to access parameters

	push es			! save es
        push bx

	mov es,4[bp]		! load es with segment value
	mov bx,6[bp]		! load bx with offset from segment
	seg es			! go get the byte
	movb al,[bx]		! al = byte
	xorb ah,ah		! ax = byte

        pop bx
	pop es			! restore es

        mov bp,sp
	pop bp			! restore bp
	ret			! return to caller


!*===========================================================================*
!*				put_byte				     *
!*===========================================================================*
! This routine is used to put a word to anywhere in memory.
! The call is:
!           put_byte[char,segment,offset]
! where
!     char is a byte
!     'segment' is a segment
!     'offset'  is the offset from the segment
_put_byte:
	push bp			! save bp
	mov  bp,sp		! we need to access parameters

	push es			! save es
        push bx

	mov  es,6[bp]   	! load es with segment value
	mov  bx,8[bp]		! load bx with offset from segment
        movb al,4[bp]           ! load byte in aL
	seg  es			! go put the byte to [ES, BX]
	movb  [bx],al		! there it goes

        pop  bx                 ! restore bx
	pop  es			! restore es

        mov  bp,sp
	pop  bp			! restore bp
	ret			! return to caller
