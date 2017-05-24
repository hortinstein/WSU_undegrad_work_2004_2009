int my_rmdir(int device, char* name)
{
	//struct stat file;
    int r = 0;int i =0;
	int ino = 0;
	MINODE* mip = 0;
    //char pathname[256];
    char parent[256];
    char child[256];
    char fullname[256];
    MINODE* pip;
    //char* temp;
    //printf("1\n");
    if(name == NULL)
    {
        output("Cant remove a directory without a name");
        return(1);
    }
    if (name[0] == '/') 
    {
        strcpy(parent, name);
        strcpy(child, name);
        my_dirname(parent);
        my_basename(child);
    }
    else
    {
        strcpy(parent, running->cwd->name);
        strcpy(child, name);
    }
    printf("Parent %s\n", parent);
    printf("Child %s\n", child);
    //return 1;
    pip = iget(device, getino(device, parent));


	 if (0 == is_dir(pip) )
	 {

		irelease(mip);
        output("File could not be identified as a directory");
		return -1;
	 }
	 if (pip->refCount > 2)
	 {
		//output("Too many refCount's, cannot remove at this time");
        //return 1;
	 }
	 else
	 {

        strcpy(fullname, parent);
        if(0 != strcmp(fullname, "/") )
        {
            strcat(fullname, "/");
        }
        strcat(fullname, child);
        ino = getino(device, fullname);
        mip = iget(device, ino);
        if( 0 !=rm_child(pip, ino, child) )
            return 1;
	 }
    printf("1\n");
    printf("%d\n", mip->i_node.i_block[i]);

    for (i=0; i<12; i++)
    {
        printf("%d %d", i, mip->i_node.i_block[i]);
        if (mip->i_node.i_block[i]==0)
            break;
        //printf("%d %d", i, mip->i_node.i_block[i]);
        bdalloc(device, mip->i_node.i_block[i]);
    }
    printf("2\n");
    idalloc(device, mip->ino);
    printf("3\n");
    pip->dirty = 1;
    irelease(pip);
    printf("4\n");
    return 0;
//   8. deallocate its block and inode
//     for (i=0; i<12; i++){
//         if (mip->INODE.i_block[i]==0)
//             continue;
//         bdalloc(mip->dev, mip->INODE.i_block[i]);
//     }
//     idalloc(mip->dev, mip->ino);
//     mip->refCount = 0;

//     decrement pip's link_count by 1; 
//     touch pip's atime, mtime fields;
//     mark pip dirty;
//     iput(pip);
//     return(0);
}
int rm_child(MINODE* pip, int ino, char* child)
{
    int blk = 0;
    int i;
    char* cp;
    char* temp[256];
    int count;
    DIR   *prev; 
    ip = &pip->i_node;
    for (i = 0; i < 12; i++)
    {
        blk = ip->i_block[i];
        //printf("i_block[%d] = %d\n", i, blk);  // print blk number
        if (blk==0)
        {
            break;
        }
        get_block(device, rbuf, blk); // get block contents into rbuf[] 
    
        dp = (DIR *)rbuf;     // as DIR entries
        cp = rbuf;
        count = 0;
        while(cp < &rbuf[BLOCK_SIZE])
        {
            bzero(temp, 256);
            strncpy((char*)temp, dp->name, dp->name_len);
            if( 0 == strcmp((char*)temp, child) )
            {
                if(count == 0)
                {
                    dp->inode = 0;
                    return 0;
                }
                else
                {
                    //printf("Prev\n";
                    //printf("Name
                    //printf("here\n%d\n%d\n", prev->rec_len,dp->rec_len);
                    
                    prev->rec_len += dp->rec_len;
                    put_block(device, rbuf, blk);
                    return 0;
                }
            }
            prev = dp;
            cp += dp->rec_len;
            dp = (DIR *)cp;
            count++;
        }
    }
}
int rm(char *name)
{
	struct stat file;
    int r = 0;int i =0;
	int ino = 0;
	MINODE* mip = 0;
    //char pathname[256];
    char parent[256];
    char child[256];
    char fullname[256];
    MINODE* pip;
    //char* temp;
    //printf("1\n");
    if(name == NULL)
    {
        output("Cant rmove without a name");
        return(1);
    }
    if (name[0] == '/') 
    {
        strcpy(parent, name);
        strcpy(child, name);
        my_dirname(parent);
        my_basename(child);
    }
    else
    {
        strcpy(parent, running->cwd->name);
        strcpy(child, name);
    }
    printf("Parent %s\n", parent);
    printf("Child %s\n", child);
    pip = iget(device, getino(device, parent));


	 if (1 == is_dir(pip) )
	 {

		irelease(mip);
        output("File could not be identified");
		return -1;
	 }
	 if (pip->refCount > 2)
	 {
		//output("Too many refCount's, cannot remove at this time");
        //return 1;
	 }
	 else
	 {

        strcpy(fullname, parent);
        if(0 != strcmp(fullname, "/") )
        {
            strcat(fullname, "/");
        }
        strcat(fullname, child);
        ino = getino(device, fullname);
        mip = iget(device, ino);
        if( 0 !=rm_child(pip, ino, child) )
            return 1;
	 }
    printf("1\n");
    printf("%d\n", mip->i_node.i_block[i]);

    for (i=0; i<12; i++)
    {
        printf("%d %d", i, mip->i_node.i_block[i]);
        if (mip->i_node.i_block[i]==0)
            break;
        //printf("%d %d", i, mip->i_node.i_block[i]);
        bdalloc(device, mip->i_node.i_block[i]);
    }

    idalloc(device, mip->ino);

    pip->dirty = 1;
    irelease(pip);

    return 0;

}
