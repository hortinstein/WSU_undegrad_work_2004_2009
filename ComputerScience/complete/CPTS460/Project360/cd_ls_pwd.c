void my_ls(char* love_letter)
{
    char* where;
    int i_num;
    int n_blk;
    int i;
    char* cp;
    int num = 0;
    int blk;
    char* temp[256];
    if(love_letter == NULL )
    {
        
        where = running->cwd->name;
        //printf("Where %s\n", where);
        if( 0 == strcmp(where, "/") )
        {

            get_block(device, rbuf, inode_start);
            ip = (INODE*)rbuf + 1;
        }
        else
        {
            //i_num = getino(device, where);
            //printf("%d\n", i_num);
            i_num = running->cwd->ino;
            n_blk = (i_num - 1)/INODES_PER_BLOCK + inode_start;
            i_num = (i_num - 1)%INODES_PER_BLOCK;
            get_block(device, rbuf, n_blk);
            ip = (INODE*)rbuf + i_num;
        }
    }
    else
    {
        where = love_letter;
        //printf("%s\n", where);
        //exit(1);
        i_num = getino(device, where);
        printf("%d\n", i_num);

        n_blk = (i_num - 1)/INODES_PER_BLOCK + inode_start;
        i_num = (i_num - 1)%INODES_PER_BLOCK;
        get_block(device, rbuf, n_blk);
        ip = (INODE*)rbuf + i_num;
    }
    
    for (i = 0; i < 12; i++)
    {
        blk = ip->i_block[i];
        printf("i_block[%d] = %d\n", i, blk);  // print blk number
        if (blk==0)
        {
            break;
        }
        get_block(device, rbuf, blk); // get block contents into rbuf[] 
    
        dp = (DIR *)rbuf;     // as DIR entries
        cp = rbuf;
        while(cp < &rbuf[BLOCK_SIZE])
        {
            bzero(temp, 256);
            strncpy((char*)temp, dp->name, dp->name_len);
            printf("%4d %4d %4d  %s\n", dp->inode, dp->rec_len, dp->name_len, temp);
            if( 0 == strcmp((char*)temp, where) )
            {
                num = dp->inode;
            }
            cp += dp->rec_len;
            dp = (DIR *)cp;
        }
    }

}
void my_pwd()
{
    printf("%s\n",running->cwd->name);
}

int my_cd(char * SSI)
{
    char* my_name;
    char* my_pname;
    char full[256];
    char temp[256];
    char prev;
    int size = 0;
    int counter = 0;
    int counter2 = 0;
    int i_num = 0;
    int i_parent = 0;
    MINODE* tp;
  
    if (SSI == NULL || (SSI[0] == '/' && strlen(SSI) == 1))
    {
        i_num = root->ino;
        strcpy(temp, "/");
    }
    else
    {
        if (SSI[0] ==  '/')
        {
            strcpy(full, SSI);
        }
        else
        { 
            strcpy(full, running->cwd->name);
            size =  strlen(full);
            if ( full[size-1] != '/')
                strcat(full, "/");
            strcat(full, SSI);
        }
        //remove end /////'s
        for(size = strlen(full)-1; full[size] == '/' && size != 0; size--)
        {
            full[size] = '\0';
        }
        //remove and mult /'s
        strcpy(temp, full);
        for(counter2 = 0; counter2 != strlen(temp); counter2++)
        {
            if(!(temp[counter2] == '/' && prev == '/') )
            {
                full[counter] = temp[counter2];
                full[counter+1] = '\0';
                counter++;
            }
            prev = temp[counter2];
        
        }
        strcpy(temp, full);
        i_num = getino(device, full);
        if(i_num == 0)
        {
            //printf("File not found\n");
            return(1);
        }
    }
    
    tp = iget(device, i_num);
    ip = getInode(device, i_num);
    if( 0 == is_dir(tp) )
    {
        return(1);
    }
    tp->i_node = *ip;
    tp->dev = device;
    tp->ino = i_num;
    tp->refCount = 1;
    tp->dirty = 0;
    tp->mounted = 0;
    tp->mountptr = &mountTable[0];
    strcpy(tp->name, temp);

    running->cwd->refCount--;
    running->cwd = tp;
    return(0);
}












