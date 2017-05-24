/***********************************************************************
 * get_word
 * Description: Uses get_byte() from ts.s to get a word (16-bits) from
 *              a given offset in a given segment.
 * Params:      ushort segment - segment to fetch the data bits from
 *              ushort offset - the offset from the beginning of the
 *                  given segment
 * Return:      ushort w - the word fetched from the given segment and
 *                  offset
 *
 **********************************************************************/
ushort get_word( segment, offset ) ushort segment; ushort offset;
{
    /* The hi and low bits of the total word. */
    uchar hi = 0x00;
    uchar lo = 0x00;

    /* The whole word that we will return. */
    ushort w = 0x0000;

    /* Get the first byte from the selected offset in the segment.  We
     * increment offset by 1 to go to the byte immediately after in the
     * same segment */
    lo = get_byte( segment, offset++ );
    hi = get_byte( segment, offset );

    /* To get a full word out of these two 8-bit variables, we must cast
     * them to 16-bit words.  So now both will become:
     *
     *      hi = 0x00dd
     *      lo = 0x00dd
     *
     *      d - the data from the segment.
     *
     * Now, we shift the high bits over to the left by 8 bits.  So now
     * we get:
     *
     *      hi = 0xdd00
     *
     * Now that we have the bits in the right area, we OR the values
     * together to get the full word:
     *
     *      hi | lo = 0xdddd */
    w = (ushort)( hi << 8 ) | (ushort)lo;

    return w;
}

/***********************************************************************
 * put_word
 * Description: Uses put_byte() from ts.s to put a given word (16-bits)
 *              from a given offset in a given segment.
 * Params:      ushort segment - segment to put the data bits in
 *              ushort offset - the offset from the beginning of the
 *                  given segment
 *              ushort w - the word to put into the segment
 * Return:      int success/fail - SUCCESS or FAIL
 *
 **********************************************************************/
ushort put_word( w, segment, offset ) ushort w; ushort segment; ushort offset;
{
    /* Since we are using put_byte(), we have to convert the 16-bit
     * word to two 8-bit bytes.  To do this, we take the word and AND it
     * with 0xFF00 for hi and 0x00FF for lo.  The following shows why:
     *
     *      0xFF00 & 0xhhll = 0xhh00        <== hi bits only
     *      0x00FF & 0xhhll = 0x00ll        <== lo bits only
     *
     * Then we cast the ANDed words to bytes, BUT the hi bits will
     * be truncated.  So, we have to shift those bits over to the end:
     *
     *      0xhh00 >> 8 = 0x00hh
     *
     * Now we have the hi bits and lo bits in two seperate bytes. */
    uchar hi = (uchar)( ( 0xFF00 & w ) >> 8 );
    uchar lo = (uchar)( 0x00FF & w );

    /* Put the lo bits first, increment the offset by one byte, then
     * put the hi bits in. */
    put_byte( lo, segment, offset++ );
    put_byte( hi, segment, offset );

    return SUCCESS;
}
