/****************************************************************************
               serial.c file for SERIAL DRIVER
Each serial terminal is represented by a stty struct consisting of 
     INPUT section = a circular buffer with incount  chars
    OUTPUT section = a circular buffer with outcount chars
Process and interrupt handler synchronize by sleep()/wakeup()
***************************************************************************/

/**************** CONSTANTS ***********************/
#define BUFLEN      80
#define NSTTY        2    /* number of serial ports */

/* offset from serial ports base */
#define DATA         0   /* Data reg for Rx, Tx   */
#define DIVL         0   /* When used as divisor  */
#define DIVH         1   /* to generate baud rate */
#define IER          1   /* Interrupt Enable reg  */
#define IIR          2   /* Interrupt ID rer      */
#define LCR          3   /* Line Control reg      */
#define MCR          4   /* Modem Control reg     */
#define LSR          5   /* Line Status reg       */
#define MSR          6   /* Modem Status reg      */

/**** The serial terminal data structure ****/
typedef struct stty {

   /* I/O port base address */
   int port;

   /* input buffer */
   char inbuf[BUFLEN];
   int inhead, intail, incount;

   /* output buffer */
   char outbuf[BUFLEN];
   int outhead, outtail, outcount;

  // coontrol section: (erase, kill, interrupt keys, etc) 
  // NOT shown

} STTY;

STTY stty[NSTTY];  // actual stty data structure; one per terminal
   
/************ serial ports initialization ***************/

char *message[2] = { "Serial Port 0 Ready\n\r\007", "Serial Port 1 Ready\n\r\007"};

int sinit()         // init() function
{
  int i;  
  STTY *t;

  /* initialize stty[] and serial port control registers */

  for (i = 0; i < NSTTY; i++){
      t = &stty[i];

      /* initialize data structures and pointers */
      if (i==0)
          t->port = 0x3F8;    /* COM1 base address */
      else
          t->port = 0x2F8;    /* COM2 base address */  

      printf("sinit : port %x\n", t->port);
      t->inhead = t->intail = t->incount = 0;
      t->outhead = t->outtail = t->outcount = 0;

    lock();  // CLI; no interrupts
      out_byte(t->port+IER,  0x00);  /* disable serial port interrupts */

      out_byte(t->port+LCR,  0x80);  /* ready to use 3f9,3f8 as divisor */
      out_byte(t->port+DIVH, 0x00);
      out_byte(t->port+DIVL, 12);    /* divisor = 12 ===> 9600 bauds */

      /******** term 9600 /dev/ttyS0: 8 bits/char, no parity *************/ 
      out_byte(t->port+LCR, 0x03); 

      /*******************************************************************
        Writing to 3fc ModemControl tells modem : DTR, then RTS ==>
        let modem respond as a DCE.  Here we must let the (crossed)
        cable tell the TVI terminal that the "DCE" has DSR and CTS.  
        So we turn the port's DTR and RTS on.
      ********************************************************************/

      out_byte(t->port+MCR, 0x0B);  /* 1011 ==> INTERRUPT, RTS, DTR on   */
      out_byte(t->port+IER, 0x01);  /* Enable Rx interrupt, Tx off */

    unlock();
    
    enable_irq(4-i);  // COM1: IRQ4; COM2: IRQ3

    /* show greeting message */
    sputline(i, message[i]);
  }
}  
         
//==================== LOWER HALF ROUTINES (Interrupt handlers) =======================
int s0handler()
{
  shandler(0);
}

int s1handler()
{
  shandler(1);
}

int shandler(port) int port;
{  
   STTY *t;
   int IntID, LineStatus, ModemStatus, intType, c;

   t = &stty[port];            /* IRQ 4 interrupt : COM1 = stty[0] */

   IntID     = in_byte(t->port+IIR);       /* read InterruptID Reg */
   LineStatus= in_byte(t->port+LSR);       /* read LineStatus  Reg */    
   ModemStatus=in_byte(t->port+MSR);       /* read ModemStatus Reg */

   intType = IntID & 7;     /* mask out all except the lowest 3 bits */
   switch(intType){
      case 6 : do_errors(t);  break;   /* 110 = errors */
      case 4 : do_rx(t);      break;   /* 100 = rx interrupt */
      case 2 : do_tx(t);      break;   /* 010 = tx interrupt */
      case 0 : do_modem(t);   break;   /* 000 = modem interrupt */
   }
   out_byte(0x20, 0x20);   /* reenable the 8259 controller */ 
}

int do_errors() { printf("under construction\n"); }

int do_modem()  { printf("don't have a modem\n"); }

int do_rx(t) STTY *t;           /* rx interrupt */
{ 
  int c;

  c = in_byte(t->port) & 0x7F;  /* read the ASCII char from port */

  printf("\n%x rx_interrupt : c=%c", t->port, c);

  if (t->incount >= BUFLEN){    // if input buf is full, discard
    out_byte(t->port, 007);     // but sound warning beep
    return;
  }

  t->inbuf[t->inhead++] = c;   /* put char into circular inbuf[] */
  t->inhead %= BUFLEN;         /* advance inhead */
  t->incount++;

  wakeup(&t->incount);         // wakeup process that may be sleeping
}      

int do_tx(t) STTY *t;          // tx_interrupt
{
  int c;
  
  if (t->outcount==0){          // nothing to do 
      out_byte(t->port+IER, 0x01);
      return;
  }
  c = t->outbuf[t->outtail++];
  t->outtail %= BUFLEN;
  t->outcount--;

  out_byte(t->port, c);

  wakeup(&t->outcount);
}

/**************** Upper half routines CALLED BY process **************: 
          sgetc()/sputs() which interact with Interrupt handlers  
**********************************************************************/

int sgetc(port) int port;
{ 
  STTY *t;
  int c;

  t = &stty[port];

  while (t->incount==0)
     sleep(&t->incount);

  lock();             /* disable interrupts */
      c = t->inbuf[t->intail++];
      t->intail %= BUFLEN;
      t->incount--;
  unlock();
  return(c);
}

int sputc(port, c) int port, c;
{
    STTY *t = &stty[port];

    while(t->outcount==BUFLEN)
      sleep(&t->outcount);

    lock();
    if (t->outcount==0){
       out_byte(t->port, c);
       out_byte(t->port+IER, 0x03);
    }
    else{
         t->outbuf[t->outhead++] = c;
         t->outhead %= BUFLEN;
         t->outcount++;
    }
    unlock();
}
/********************* END OF SERIAL DRIVER *************************************/


/***** line mode functions sgetline()/sputline() based on sgetc()/sputc() ************/

int sgetline(port, line) int port; char *line;
{  
   while ( (*line = sgetc(port)) != '\r'){
          line++; 
   }
   *(line) = 0;            /* change \r to null char */
   return strlen(line);
}

int sputline(port, line) int port; char *line;
{
   while (*line){
         sputc(port, *line);
         line++;
   }
}

/******* User Interface fucntions to serial ports ************/
int sgets()
{
  char line[64];
  int port;

  printf("enter port # (0|1):");
  port = getc() - '0';
  printf("port=%d\n", port);

  sputline(port, "enter a line from serial terminal : ");
  sgetline(port, line);
  printf("\nline=%s\n", line);
  sputline(port, line);
  sputline(port,"\n\r");
}

int sputs()
{
  char line[64];
  int port;

  printf("enter port # (0|1):");
  port = getc() - '0';

  printf("enter a line : ");
  gets(line);
  strcat(line, "\n\r");
  printf("to serial port %d: line=%s\n", port, line);

  sputline(port, line);
  printf("done\n");
}
  
