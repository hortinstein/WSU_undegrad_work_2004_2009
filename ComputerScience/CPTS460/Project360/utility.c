//(1). Block utility functions

int get_block(int dev,char* buf,int blkno)
{
    lseek(dev, (long)(BLOCK_SIZE * blkno), 0);
    return( read(dev, buf, BLOCK_SIZE) );
}

int put_block(int dev,char* buf,int blkno)
{
    lseek(dev, (long)(BLOCK_SIZE* blkno), 0);
    return( write(dev, buf, BLOCK_SIZE) );
}
int clr_bit(char *c, int bit)
{
    int i,j;
	i = bit/8;
	j = bit%8;
    c[i] |= (0<<j);
}
int tst_bit(int bit, char* c)
{ 
    int i,j;
	i = bit/8;
	j = bit%8;
	return( c[i]& (1<<j));
}
int set_bit(int bit,char *c)
{
    int i,j;
	i = bit/8;
	j = bit%8;
    c[i] |= (1<<j);
}
unsigned long idalloc(int dev, int ino)
{
  int i;  
  char buf[BLOCK_SIZE];

  // get inode bitmap block
  get_block(dev, buf, 4);
  clr_bit(buf, ino-1);         // assume you have clr_bit() function 

  // write buf back
  put_block(dev, buf, 4);

  // update free inode count in SUPER and GD
  sp->s_free_inodes_count++;
  gp->bg_free_inodes_count++;
}
unsigned long bdalloc(int dev, int block_d)
{
     int i;  
  char buf[BLOCK_SIZE];

  // get inode bitmap block
  get_block(dev,buf, 4);
  clr_bit(buf, block_d-1);         // assume you have clr_bit() function 

  // write buf back
  put_block(dev, buf, 4);

  // update free inode count in SUPER and GD
  sp->s_free_blocks_count++;
  gp->bg_free_blocks_count++;
}
unsigned long ialloc(int dev)
{
    char *c;
    int i_num;
    int inode_count;
    int i = 0;
    int bit = 0;
    int counter = 0;
    int found = 0;
    get_block(device, rbuf, 1);
    sp = (SUPER *)rbuf;
    inode_count = sp->s_inodes_count;
    if( sp->s_free_inodes_count == 0 )
        return(0);
    get_block(device,rbuf,4);
    c = rbuf + 1;
    for(i = 0; counter*8 <= inode_count&& found == 0; i++)
    {
        if( 0 == tst_bit(bit, c) )
        {
            i_num = (8+counter*8+bit+1);
            set_bit(bit, c);
            put_block(device, rbuf, 4);
            sp->s_free_inodes_count--;
            gp->bg_free_inodes_count--;
            return(8+counter*8+bit+1);
        }
        if(bit >= 7)
        {
            bit = -1;
            counter++;
            c++;
        }
        bit++;
        
    }
    if( found == 0)
    {
        return(0);
    }
    return(i_num);
}
unsigned long balloc(int dev)
{
    char *c;
    int i_num;
    int blocks_count;
    int i = 0;
    int bit = 0;
    int counter = 0;
    int found = 0;
    get_block(device, rbuf, 1);
    sp = (SUPER *)rbuf;
    blocks_count = sp->s_free_blocks_count;
    if( blocks_count == 0 )
        return(0);
    get_block(device,rbuf,3);
    c = rbuf + 1;
    for(i = 0; counter*8 <= blocks_count&& found == 0; i++)
    {
        if( 0 == tst_bit(bit, c) )
        {
            found = 1;
            i_num = (8+counter*8+bit+1);
            set_bit(bit, c);
            put_block(device, rbuf, 3);
            sp->s_free_blocks_count--;
            gp->bg_free_blocks_count--;
        }
        if(bit >= 7)
        {
            bit = -1;
            counter++;
            c++;
        }
        bit++;
        
    }
    if( found == 0)
    {
        return(0);
    }
    return(i_num);
}

INODE* getInode(int dev, int ino)
{
    int n_blk = 0;
    int i_num = 0;
    n_blk = (ino - 1)/INODES_PER_BLOCK + inode_start;
    i_num = (ino - 1)%INODES_PER_BLOCK;
    get_block(device, rbuf, n_blk);
    return( (INODE*)rbuf + i_num );
}
token_path(char* pathname)
{
    char* tp;
    int counter = 0;
    tp = strtok(pathname, "/"); 
    while( tp != NULL)
    {
        path[counter] = tp;
        counter++;
        tp = strtok(NULL, "/");
    }
    path[counter] = NULL;
}
unsigned int inode_helper(char *pathname)
{
    int i;
    char* cp;
    int num = 0;
    int blk;
    char* temp[256];
    
    for (i = 0; i < 12; i++)
    {
        blk = ip->i_block[i];
        if (blk==0)
        {
            break;
        }
        get_block(device, rbuf, blk);
    
        dp = (DIR *)rbuf;
        cp = rbuf;
        while(cp < &rbuf[BLOCK_SIZE])
        {
            bzero(temp, 256);
            strncpy((char*)temp, dp->name, dp->name_len);
            if( 0 == strcmp((char*)temp, pathname) )
            {
                num = dp->inode;
            }
            cp += dp->rec_len;
            dp = (DIR *)cp;
        }
    }
    return(num);
}
int getino(int dev, char *pathname)
{
    int counter;
    int i_num = 0;
    int i_num2 = 0;
    int n_blk = 0;
    if(0 == strcmp(pathname, "/") )
        return root->ino;
    token_path(pathname);

    get_block(device, rbuf, inode_start);
    ip = (INODE*)rbuf+1;


    for(counter = 0;  path[counter] != NULL ; counter++)
    {

        i_num = inode_helper(path[counter]);

        if(i_num != 0)
        {
            n_blk = (i_num - 1)/INODES_PER_BLOCK + inode_start;
            i_num2 = (i_num - 1)%INODES_PER_BLOCK;
            get_block(device, rbuf, n_blk);
            ip = (INODE*)rbuf+i_num2;
        }
        else
        {
            break;
        }
    }
    return(i_num);
}

int irelease(MINODE *mip)
{
    int i = 0;
    int i_num = mip->ino;
    int n_blk;
    int i_num2;
    INODE* c;
    if(mip->dirty == 0)
        return(1);
    //printf("Releaseing ino %d\n", mip->ino);
    if(mip->ino == 2)
    {
        get_block(device, rbuf, inode_start);
        c = (INODE*)rbuf+1;
        *c = mip->i_node;
        put_block(device, rbuf,inode_start);
        return(0);
    }

    n_blk = (i_num - 1)/INODES_PER_BLOCK + inode_start;
    i_num2 = (i_num - 1)%INODES_PER_BLOCK;
    get_block(device, rbuf, n_blk);
    c = (INODE*)rbuf+i_num2;
    *c = mip->i_node;
    //printf("RES 1] %d\n", mip->i_node.i_block[1]);
    put_block(device, rbuf,n_blk);
}
MINODE *iget(int dev,int ino)
{
	int counter = 0;
    int myino;
    int parentino;
    char name[256];
    ip = getInode(device, ino);
    for(counter = 0; counter < NMINODES; counter++)
    {
        if ( Minode[counter].ino == ino)
        {
            Minode[counter].refCount++;
            return (&Minode[counter]);
        }
    }
    for(counter = 0; counter < NMINODES; counter++)
    {
        if ( Minode[counter].refCount <= 0 )
        {
            if ( Minode[counter].dirty == 1)
            {
                irelease(&Minode[counter]);
            }
            
            Minode[counter].i_node = *ip;
            Minode[counter].dev = device;
            Minode[counter].ino = ino;
            Minode[counter].refCount = 1;
            Minode[counter].dirty = 0;
            Minode[counter].mounted = 0;
            findmyname(running->cwd, ino, name);
            //printf("My name %s\n", name); 
            //exit(1);
            strcpy(Minode[counter].name, name);
            return (&Minode[counter]);   
        }
    }
    return (0);
}
int findmyname(MINODE *parent, unsigned long myino, char *myname) 
{
    int i;
    char* cp;
    int num = 0;
    int blk;
    char* temp[256];
    ip = &parent->i_node;
    for (i = 0; i < 12; i++)
    {
        blk = ip->i_block[i];
        if (blk==0)
        {

            break;
        }
        get_block(device, rbuf, blk);
    
        dp = (DIR *)rbuf;
        cp = rbuf;
        while(cp < &rbuf[BLOCK_SIZE])
        {

            bzero(temp, 256);
            strncpy((char*)temp, dp->name, dp->name_len);
            if( dp->inode == myino )
            {
                strcpy( myname, parent->name);
                if(0 != strcmp(myname, "/"))
                    strcat( myname, "/");
                strcat( myname ,(char*)temp);
                break;
            }
            cp += dp->rec_len;
            dp = (DIR *)cp;
        }
    }
}

int findino (MINODE *mip, unsigned long *myino,unsigned long *parentino)
{
    int i;
    char* cp;
    int num = 0;
    int blk;
    char* temp[256];
    
    ip = &mip->i_node;
    for (i = 0; i < 12; i++)
    {
        blk = ip->i_block[i];
        if (blk==0)
        {

            break;
        }
        get_block(device, rbuf, blk);
    
        dp = (DIR *)rbuf;
        cp = rbuf;
        while(cp < &rbuf[BLOCK_SIZE])
        {

            bzero(temp, 256);
            strncpy((char*)temp, dp->name, dp->name_len);
            if( 0 == strcmp((char*)temp, ".") )
            {
                //printf(". :%d\n", dp->inode);
                *myino = dp->inode;
            }
            if( 0 == strcmp((char*)temp, "..") )
            {
                //printf(".. :%d\n", dp->inode);
                *myino = dp->inode;
            }
            cp += dp->rec_len;
            dp = (DIR *)cp;
        }
    }
}
int has_child (MINODE *mip, char *child)
{
    int i;
    char* cp;
    int num = 0;
    int blk;
    char* temp[256];
    
    ip = &mip->i_node;
    for (i = 0; i < 12; i++)
    {
        //printf("HAS [%d] %d", i, ip->i_block[i]);
        blk = ip->i_block[i];
        if (blk==0)
        {

            break;
        }
        get_block(device, rbuf, blk);
    
        dp = (DIR *)rbuf;
        cp = rbuf;
        while(cp < &rbuf[BLOCK_SIZE])
        {

            bzero(temp, 256);
            strncpy((char*)temp, dp->name, dp->name_len);
            
            if( 0 == strcmp((char*)temp, child) )
            {
                //printf("HAS NAME FOUND %s\n", temp);
                return(1);
            }
            cp += dp->rec_len;
            dp = (DIR *)cp;
        }
    }
    return(0);
}

