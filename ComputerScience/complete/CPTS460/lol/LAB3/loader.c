#include "file_functions.c"
int tst_bit(bit, c)unsigned short bit; unsigned short* c;
{ 
    int i,j;
	i = bit/16;
	j = bit%16;
	return( c[i]& (1<<j));
}
int set_bit(bit, c)unsigned short bit; unsigned char *c;
{
    int i,j;
	i = bit/8;
	j = bit%8;
    c[i] |= (1<<j);
}

u16 get_word(segment, offset) u16 segment; u16 offset;
{

	u16 r = 0x0000;
	u8 lo = get_byte(segment,offset);
	offset++;
	u8 hi = get_byte(segment,offset);
	
	r = (u16)lo | (u16)hi <<8);
	return(r);
}

int put_word(word, segment, offset) u16 word; u16 segment; u16 offset;
{
	u8 part1 = (u8)(word & 0x00FF);
	u8 part2 = (u8)((word & 0xFF00) >> 8);

	put_byte(part1, segment, offset);
	offset += 1;
	put_byte(part2, segment, offset);
}
load(filename, segment)char* filename; int segment;
{
	INODE* file;
	u16* num; 
	//u8 num2;
	int num2;
	u16* indirect = 0;
	int offset = 0;
	char mbuf[1024]; 
	char mbuf2[1024];
	char mbuf3[1024];
	u16 i = 0;
	u16 ino = getino(filename);
	if( ino == 0)
		return 0;
	myprintf("Inode found %d\n", ino);
	file = getInode(ino);
	get_block((u16)file->i_block[0], mbuf2);
	hp = (struct header*) mbuf2;
	myprintf("Sep: %x\n", (int)hp->sep);
	myprintf("Gap: %x\n", (int)hp->gap);
	myprintf("Text Size: %x\n", (int)hp->tsize);
	myprintf("Data Size: %x\n", (int)hp->dsize);
	myprintf("BSS Size: %x\n", (int)hp->bsize);
	myprintf("%x\n", (int)hp->zero);
	myprintf("Total: %x\n", (int)(hp->tsize+hp->dsize+hp->bsize));
	myprintf("Symbol: %x\n", (int)hp->ssize);
	
	get_block((u16)file->i_block[12], mbuf3);
	myprintf("Loading Direct\n");
	for(i = 0; i < 12; i++)
	{
		if(file->i_block[i] == 0)
			break;
		myprintf("i_block[%d]: %d\n", (int)i, (int)file->i_block[i]);
		get_block((u16)file->i_block[i], mbuf);

		for(num2 = 0; num2 < 1024; num2 = num2+2)
		{
			put_word(((u16*)mbuf)[num2/2], segment,(u16)(i*1024+num2));
		}
	}
	if( i == 12)
	{
		myprintf("Loading indirect\n");
		for(indirect = (u16*)mbuf3; indirect < &mbuf3[1024]; indirect += 2)
		{
			if (*indirect == 0)
				break;
			myprintf("Indirect Block: %d\n", *indirect);
		    get_block((u16)*indirect, mbuf2);
			for(num2 = 0;num2 < 1024;num2++)
			{
				put_byte(mbuf[num2],segment,(u16)(i*1024+num2));
			}
		
		}
	}
    for (i=0; i < (int)(hp->tsize + hp->dsize); i++)
    {
        put_byte(get_byte(segment, (u16)(i + 32)), segment, (u16)i);
    }
	for (i; i < (int)(hp->bsize); i++)
    {
        put_byte('\0', segment, (u16)i);
    }
	return 1;
}

