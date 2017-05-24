/***********************************************************************
 * io.c
 *
 * Author:      Frederick R. Ancheta
 * Date:        February 5, 2009
 * Class:       Cpt S 460
 * Assignment:  Lab 02 Prelab - Processes
 *
 * Description: This file contains the implementation of printf() and
 *              gets() for use in the t.c file.  This handles
 *              ints, longs, octal, hex, chars, and strings.  Any other
 *              datatype will not work.
 *
 **********************************************************************/

/* Tables for printing out the various datatypes using putc(). */
char * int_table = "0123456789";
char * hex_table = "0123456789ABCD";
char * oct_table = "01234567";

/***********************************************************************
 * gets
 * Description: Uses getc() from s.s to get a string from stdin and
 *              store it in a buffer provided.  It also echoes anything
 *              typed into stdin as well.
 * Params:      char * s - the string to be printed to stdout
 * Return:      char * of the location in memory where the string was
 *              stored
 *
 **********************************************************************/
char * gets( s ) char * s;
{
    char c;

    do {
        c = getc();
        putc(c);
        *s++ = c;
    } while ( c != '\r' );

    *s-- = '\0';

    return s;
}

/***********************************************************************
 * rpi
 * Description: A recursive function that uses putc() from s.s to print
 *              out the digits in an integer by calling itself on the
 *              integer divided by the base (10).  It prints out the
 *              remainder of integer divided by the base (10).
 *
 *              Note: This is used as a helper to printd().
 *
 * Params:      int i - the integer to be printed out
 * Return:      None
 *
 **********************************************************************/
void rpi( i ) int i;
{
    char c;

    if ( i ) {
        c = int_table[i%10];
        rpi( i/10 );
        putc( c );
    }
}

/***********************************************************************
 * printd
 * Description: Uses putc() from s.s to get print out an integer value
 *              recursively.  It also checks if the int is negative
 *              prior to printing it out.
 *
 *              Note: This is used as a helper to printf().
 *
 * Params:      int i - the integer to be printed out
 * Return:      None
 *
 **********************************************************************/
void printd( i ) int i;
{
    if ( i < 0 ) {
        putc( '-' );
        rpi( -1 * i );
    }
    else if ( i == 0 ) {
        putc( '0' );
    }
    else {
        rpi( i );
    }
}

/***********************************************************************
 * rpx
 * Description: A recursive function that uses putc() from s.s to print
 *              out the hex digits of an integer by calling itself on
 *              the integer divided by the base (16).  It prints out the
 *              remainder of integer divided by the base (16).
 *
 *              Note: This is used as a helper to printx().
 *
 * Params:      int x - the integer to be printed out as hex
 * Return:      None
 *
 **********************************************************************/
void rpx( x ) int x;
{
    char c;

    if ( x ) {
        c = hex_table[x%16];
        rpi( x/16 );
        putc( c );
    }
}

/***********************************************************************
 * printx
 * Description: Uses putc() from s.s to get print out an integer value
 *              recursively as a hex number.  Negative integers are not
 *              supported.
 *
 *              Note: This is used as a helper to printf().
 *
 * Params:      int x - the integer to be printed out
 * Return:      None
 *
 **********************************************************************/
void printx( x ) int x;
{
    putc( '0' );
    putc( 'x' );

    if ( x == 0 ) {
        putc( '0' );
    }
    else {
        rpx( x );
    }
}

/***********************************************************************
 * prints
 * Description: Uses putc() from s.s to get print out a string
 *              value.  This works as it did in Lab 1.
 *
 *              Note: This is used as a helper to printf().
 *
 * Params:      char * s - the string to be printed out
 * Return:      None
 *
 **********************************************************************/
void prints( s ) char * s;
{
    while (*s != '\0') {
        putc( *s++ );
    }
}

/***********************************************************************
 * printc
 * Description: Uses putc() from s.s to get print out a character.  This
 *              function was created for uniformity purposes.
 *
 *              Note: This is used as a helper to printf().
 *
 * Params:      char c - the char to be printed out
 * Return:      None
 *
 **********************************************************************/
void printc( c ) char c;
{
    putc( c );
}

/***********************************************************************
 * rpl
 * Description: A recursive function that uses putc() from s.s to print
 *              out the long digits of a long int by calling itself on
 *              the long int divided by the base (10).  It prints out
 *              the remainder of long int divided by the base (10).
 *
 *              Note: This is used as a helper to printl().
 *
 * Params:      long l - the long int to be printed out
 * Return:      None
 *
 **********************************************************************/
void rpl( l ) long l;
{
    char c;

    if ( l ) {
        c = int_table[l%10];
        rpi( l/10 );
        putc( c );
    }
}

/***********************************************************************
 * printd
 * Description: Uses putc() from s.s to get print out a long int value
 *              recursively.  It also checks if the long int is negative
 *              prior to printing it out.
 *
 *              Note: This is used as a helper to printf().
 *
 * Params:      long l - the long int to be printed out
 * Return:      None
 *
 **********************************************************************/
void printl( l ) long l;
{
    if ( l < 0 ) {
        putc( '-' );
        rpi( -1 * l );
    }
    else if ( l == 0 ) {
        putc( '0' );
    }
    else {
        rpi( l );
    }
}

/***********************************************************************
 * rpo
 * Description: A recursive function that uses putc() from s.s to print
 *              out the octal digits of an integer by calling itself on
 *              the integer divided by the base (8).  It prints out
 *              the remainder of the integer divided by the base (8).
 *
 *              Note: This is used as a helper to printo().
 *
 * Params:      int o - the integer to be printed out
 * Return:      None
 *
 **********************************************************************/
void rpo( o ) int o;
{
    char c;

    if ( o ) {
        c = oct_table[o%8];
        rpo( o/8 );
        putc( c );
    }
}

/***********************************************************************
 * printo
 * Description: Uses putc() from s.s to get print out an integer value
 *              recursively as an octal number.  Negative integers are
 *              not supported.
 *
 *              Note: This is used as a helper to printf().
 *
 * Params:      int o - the integer to be printed out as octal
 * Return:      None
 *
 **********************************************************************/
void printo( o ) int o;
{
    putc( '0' );
    putc( 'o' );

    if ( o == 0 ) {
        putc( '0' );
    }
    else {
        rpo( o );
    }
}

/***********************************************************************
 * printf
 * Description: Uses putc() from s.s to print out a string to stdout.
 *              This function also takes format strings to print out
 *              several different datatypes within the string itself.
 *              Currently, printf() supports the following datatypes:
 *
 *              %d      Integers
 *              %l      Long Integers
 *              %s      Char * Strings
 *              %c      Characters
 *              %x      Hexadecimals
 *              %o      Octals
 *
 * Params:      char * s - the format string to be printed to stdout
 * Return:      None
 *
 **********************************************************************/
void printf( s ) char * s;
{
    /* ip is for browsing through the arguments in printf() */
    unsigned short * ip = &s + 1;

    while (*s != '\0') {
        /* Check for format string! */
        if ( *s == '%' ) {
            s++;
            switch ( *s ) {
                case 'd':           /* Integers */
                    printd( *ip++ );
                    break;
                case 's':           /* Strings */
                    prints( *ip++ );
                    break;
                case 'x':           /* Hexadecimals */
                    putc( '0' );
                    putc( 'x' );
                    printx( *ip++ );
                    break;
                case 'c':           /* Chars */
                    printc( *ip++ );
                    break;
                case 'o':           /* Octals */
                    putc( '0' );
                    putc( 'o' );
                    printo( *ip++ );
                    break;
                case 'l':           /* Long Ints */
                    printl( *(long *)ip );
                    ip += 2;
                    break;

                default:    break;
            }
            *s++;
        }

        if ( *s == '\n' ) {
            putc( '\r' );
        }

        putc( *s++ );
    }
}

