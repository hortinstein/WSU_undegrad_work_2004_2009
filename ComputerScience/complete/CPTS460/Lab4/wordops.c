//get_word uses get byte (implemented by kc) to retrieve a certain byte and combine it to return a word
unsigned short get_word(segment, offset) unsigned short segment; unsigned short offset;
{
	char hi=0x00;
	char low=0x00;//8 bit vars to store the high and low bits of the word
	unsigned short totalword = 0x00;//another variable to store the total word after retrieving
	hi = get_byte( segment, offset+1);
	low = get_byte( segment, offset);
	totalword += hi;
	totalword*= 256;//shifting the high byte into proper position
	totalword+=(unsigned short)(low);//making sure that the totalword includes low
	return totalword; //returns the total word back to the user
}

//put_word uses put byte (implemented by kc) to put a certain
unsigned short put_word(w,segment, offset) unsigned short segment; unsigned short offset;
{
	char hi=0x00; //higher 8 bits of the word
	char low=0x00; //lower 8 bits of the word
	hi = ((w & 0xFF00)/256);//getting the high byte than shifting it
	low = (w & 0x00FF);//seperating the word
	put_byte(low,segment,offset);//adding the bytes to proper segment
	put_byte(hi,segment,offset+1);
	return 1;//1 for SUCCESS!
}


