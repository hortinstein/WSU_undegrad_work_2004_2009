        BOOTSEG =  0x9000        ! Boot block is loaded again to here.
        SSP      =   8192        ! Stack pointer at SS+8KB

.globl begtext, begdata, begbss                      ! these are needed by linker

.globl _diskr,_setVideo,_getc,_putc,_setes,_inces    ! EXPORT
.globl _main,_myprints                               ! IMPORT these 

.text                                                ! these tell as:	
begtext:                                             ! text,data,bss segments
.data                                                ! are all the same.
begdata:
.bss
begbss:
.text                                                
        !-----------------------------------------------------------------
        ! Only one SECTOR loaded at (0000,7C00). Must get entire BLOCK0 in
        !-----------------------------------------------------------------
        mov  ax,#BOOTSEG
        mov  es,ax                      ! set ES to BOOTSEG=0x9000
	
        xor  dx,dx
	xor  cx,cx
	incb cl
	xor  bx,bx
	mov  ax, #0x0202
	int  0x13                       ! READ first 2 sectors of FD0 to (ES,BX)
	
	jmpi    start,BOOTSEG           ! jump to CS=BOOTSEG, IP=start

start:
        mov     ax,cs                   ! set segment registers for CPU
        mov     ds,ax                   ! we know ES,CS=0x9E00. Let DS=CS  
        mov     ss,ax                   ! SS = CS ===> all point at 0x9000
        mov     sp,#SSP                 ! SP = 8KB,    at 0x9000 + 8KB

        call _main                      ! call main() in C
     
        test  ax, ax                    ! check return value from main()
        jne   error                     ! return nonzero if error
        jmpi  0, 0x1000                 ! jump to (0x1000,0) to start MTX
 
       !---------------------------------------
       ! diskr[cyl, head, sector, buf]
       !        4     6     8      10
       !---------------------------------------
_diskr:                             
        push  bp
	mov   bp,sp            ! bp = stack frame pointer

        movb  dl, #0x00        ! drive 0=FD0
        movb  dh, 6[bp]        ! head
        movb  cl, 8[bp]        ! sector
	incb  cl               ! inc sector by 1 to suit BIOS
        movb  ch, 4[bp]        ! cyl
        mov   bx, 10[bp]       ! BX=buf ==> memory addr=(ES,BX)
        mov   ax, #0x0202      ! READ 2 sectors to (EX, BX)
	
        int  0x13              ! call BIOS to read the block 
        jb   error             ! to error if CarryBit is on [read failed]

        pop  bp                
	ret
	
        !--------------------------------
        ! setVideo() : clear screen, home cursor
        !--------------------------------
_setVideo:	
        mov     ax, #0x0012
        int     0x10                    ! call BIOS to do it

        mov     ax, #0x0200             ! Home the cursor
        xor     bx, bx
        xor     dx, dx
        int     0x10                    ! call BIOS to home cursor 
        ret

        !---------------------------------------------
        !  char getc()   function: returns a char
        !---------------------------------------------
_getc:
        xorb   ah,ah           ! clear ah
        int    0x16            ! call BIOS to get a char in AX
        ret 

        !----------------------------------------------
        ! void putc(char c)  function: print a char
        !----------------------------------------------
_putc:           
        push   bp
	mov    bp,sp
	
        movb   al,4[bp]        ! get the char into aL
        movb   ah,#14          ! aH = 14
        movb   bl,#0x0B        ! bL = cyan color 
        int    0x10            ! call BIOS to display the char

        pop    bp
	ret
	        
        
_setes:  push  bp
	 mov   bp,sp

         mov   ax,4[bp]        
         mov   es,ax

	 pop   bp
	 ret
	
_inces:                         ! inces() inc ES by 0x40, or 1K
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
        call _myprints
        
        int  0x19                       ! reboot

bad:    .asciz  "Error!"

