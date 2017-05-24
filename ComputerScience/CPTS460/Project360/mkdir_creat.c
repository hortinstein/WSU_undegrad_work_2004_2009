#define ideall(len) (((len + 8 + 3)/ 4) *4)

int my_mkdir(int device, char* name)
{
	struct stat file;
    int r = 0;
    //char pathname[256];
    char parent[256];
    char child[256];
    MINODE* parent_node;
    //char* temp;
    //printf("1\n");
    if(name == NULL)
    {
        output("Cant make a directory without a name");
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
    printf("Parent  %s\n", parent);
    printf("Child %s\n", child);
    parent_node= iget(device, getino(device, parent));

    if( 1 == has_child(parent_node, child) )
    {
        output("File allready exist");
        return(1);
    }

    mkdir_helper(parent_node, child);
    return(r);
} 

int mkdir_helper(MINODE *pip, char *child)
{
    int i;
    int counter;
    int inumber;
    int b_num;
    int blk;
    int off;
    char buf[512];
    char* cp;
    int ideal_len;
    MINODE* mip;
    inumber = ialloc(device);


    //printf("here\n");
    //printf("%d\n", pip->ino);
    b_num = balloc(device);
	mip = iget(device,inumber);

	memset(&mip->i_node,0,1024);
    for(counter = 0; counter < 12;counter++)
        mip->i_node.i_block[counter] = 0;
	mip->i_node.i_block[0] = b_num;

    for(i = 1; i < 15; i++)
    {
        mip->i_node.i_block[i] = 0;
    }
    
    mip->ino = inumber;
    mip->i_node.i_mode = 0x41ED;		/* DIR and permissions */
    mip->i_node.i_uid  = running->uid;	/* Owner Uid */
    mip->i_node.i_gid =  running->gid;	/* Group Id */
    mip->i_node.i_size = 1024 ;		/* Size in bytes */
    mip->i_node.i_links_count = 2;	/* Links count */
    mip->i_node.i_atime=mip->i_node.i_ctime = mip->i_node.i_mtime = time(0L); 
    mip->i_node.i_blocks = 2;
	mip->dirty = 1;
    irelease(mip);

    mip = iget(device, inumber);
    dp = (DIR *)buf;

    dp->inode = inumber;
    strncpy(dp->name, ".", 1); 
    dp->name_len = 1;
    dp->rec_len = 12;

    cp = buf; 
    cp += dp->rec_len;
    dp = (DIR *)cp;

    dp->inode = pip->ino; 
    dp->name_len = 2;
    strncpy(dp->name, "..", 2);
    dp->rec_len = BLOCK_SIZE - 12;
    
    put_block(device,buf,b_num);

    
    
    ideal_len = ideall(strlen(child));
    ip = &pip->i_node;
    for (i = 0; i < 12; i++)
    {
        blk = ip->i_block[i];
        if (blk==0)
        {
            blk = balloc(device);
            ip->i_block[i] = blk;
            bzero(rbuf, BLOCK_SIZE);
            put_block(device, rbuf, blk);

        }
        
        get_block(device, rbuf, blk);
    
        dp = (DIR *)rbuf;
        cp = rbuf;
		int store,store2;
        while(cp < &rbuf[BLOCK_SIZE])
        {
            if( (dp->rec_len - ideall(dp->name_len))  >= ideal_len )
            {
				store = dp->rec_len;
                store2 = dp->rec_len = ideall(dp->name_len);
	            cp += dp->rec_len;
		        dp = (DIR *)cp;
				strncpy(dp->name,child,strlen(child));
				dp->inode = inumber;
				dp->name_len = strlen(child);
				dp->rec_len = store - store2;
                put_block(device, rbuf, blk);
                
				pip->refCount++;
                my_touch(device, pip->name);
                irelease(pip);
                return(0);
            }
            cp += dp->rec_len;
            dp = (DIR *)cp;
        }
    }
    output("Failed");
    return(1);
}  

#define ideall(len) (((len + 8 + 3)/ 4) *4)

int my_create(int device, char* name)
{
	struct stat file;
    int r = 0;
    //char pathname[256];
    char parent[256];
    char child[256];
    MINODE* parent_node;
    //char* temp;
    //printf("1\n");
    if(name == NULL)
    {
        output("Cant make a directory without a name");
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
    //printf("parent: %s\n", parent);
    //printf("child: %s\n", child);
    //printf("Ino: %d\n", getino(device, parent));
    parent_node= iget(device, getino(device, parent));
    //printf("here\n");
    if( 1 == has_child(parent_node, child) )
    {
        output("File allready exist");
        return(1);
    }
    //printf("here2\n");
    create_helper(parent_node, child);
    return(r);
} 

int create_helper(MINODE *pip, char *child)
{
    int i;
    int inumber;
    int b_num;
    int blk;
    int off;
    char buf[512];
    char* cp;
    int ideal_len;
    MINODE* mip;
    printf("Before\n");
    inumber = ialloc(device);
    
	//printf("ialloc %d\n", inumber);
    //b_num = (inumber - 1)/INODES_PER_BLOCK + inode_start;

    
    b_num = balloc(device);
	mip = iget(device,inumber);

	memset(&mip->i_node,0,1024);

	mip->i_node.i_block[0] = b_num;
    for(i = 1; i < 15; i++)
    {
        mip->i_node.i_block[i] = 0;
    }
    
    mip->ino = inumber;
    mip->i_node.i_mode = FILE_MODE;		/* DIR and permissions */
    mip->i_node.i_uid  = running->uid;	/* Owner Uid */
    mip->i_node.i_gid =  running->gid;	/* Group Id */
    mip->i_node.i_size = 1024 ;		/* Size in bytes */
    mip->i_node.i_links_count = 2;	/* Links count */
    mip->i_node.i_atime=mip->i_node.i_ctime = mip->i_node.i_mtime = time(0L); 
    mip->i_node.i_blocks = 2;
	mip->dirty = 1;
    irelease(mip);

    mip = iget(device, inumber);
    //printf("MIP\n");
    //printf("Ino %d\n", mip->ino);
   /// printf("Name %s\n",mip->name);
    //printf("mode %d\n", mip->i_node.i_mode);
    dp = (DIR *)buf;

    dp->inode = inumber;
    strncpy(dp->name, ".", 1); 
    dp->name_len = 1;
    dp->rec_len = 12;

    cp = buf; 
    cp += dp->rec_len;
    dp = (DIR *)cp;

    dp->inode = pip->ino; 
    dp->name_len = 2;
    strncpy(dp->name, "..", 2);
    dp->rec_len = BLOCK_SIZE - 12;

    put_block(device,buf,b_num);

    
    
    ideal_len = ideall(strlen(child));
    ip = &pip->i_node;
    for (i = 0; i < 12; i++)
    {
        blk = ip->i_block[i];
        if (blk==0)
        {
            blk = balloc(device);
            ip->i_block[i] = blk;
            bzero(rbuf, BLOCK_SIZE);
            put_block(device, rbuf, blk);
            //printf("new block %d]%d\n", i, pip->i_node.i_block[i]);
        }
        
        get_block(device, rbuf, blk);
    
        dp = (DIR *)rbuf;
        cp = rbuf;
		int store,store2;
        while(cp < &rbuf[BLOCK_SIZE])
        {
            //printf("1\n");
            //printf("Number %d\n", dp->inode);
            if( (dp->rec_len - ideall(dp->name_len))  >= ideal_len )
            {
                printf("2\n");
				store = dp->rec_len;
                store2 = dp->rec_len = ideall(dp->name_len);
	            cp += dp->rec_len;
		        dp = (DIR *)cp;
				strncpy(dp->name,child,strlen(child));
				dp->inode = inumber;
				dp->name_len = strlen(child);
				dp->rec_len = store - store2;
                //printf("Number %d\n", dp->inode);
                //printf("Name %s\n", dp->name);
                //printf("Len %d\n", dp->name_len);
                //printf("Rec %d\n", dp->rec_len);
                put_block(device, rbuf, blk);
				//pip->refCount++;
                my_touch(device, pip->name);
                irelease(pip);
                return(1);
            }
            cp += dp->rec_len;
            dp = (DIR *)cp;
        }
    }
    printf("failed\n");

}  
