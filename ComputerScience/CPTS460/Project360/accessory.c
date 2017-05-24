void output(char* output)
{
    printf("[AWESOM-O 4000: OUPUT_STATEMENT]# %s\n", output);
}
int my_dirname(char* pathname)
{
    int counter = 0;
    //char temp[256];
    //strcpy(temp, pathname);
    counter = strlen(pathname);
    counter--;
    while(counter >= 0)
    {
        if(pathname[counter] == '/')
        {
            pathname[counter] = '\0';
            return 0;
        }
        pathname[counter] = '\0';
        counter--;
    }
    return 0;
}
int my_basename(char* pathname)
{
    int counter = 0;
    int position = 0;
    char temp[256];
    //char temp[256];
    //strcpy(temp, pathname);
    for(counter = 0; counter < strlen(pathname);counter++)
    {
        if(pathname[counter] == '/')
            position = counter;
    }
    position++;
    strcpy(temp, pathname);
    for(counter = 0; position <= strlen(temp); counter++ )
    {
        pathname[counter] = temp[position];
        position++;
    }
    return 0;
}
int my_stat(int dev, char *name)
{
	struct stat file;
    char pathname[256];
    
    //char* temp;
    //printf("1\n");
    if(name == NULL)
    {
        strcpy(pathname,running->cwd->name);
    }
    else if(name[0] != '/')
    {
        //strcpy(temp, name);
        strcpy(pathname, running->cwd->name);
        if( 0 == strcmp(pathname, "/") )
        {
            //printf("2\n");
            strcat(pathname, name);
        }
        else
        {
            //printf("3\n");
            strcat(pathname, "/");
            strcat(pathname, name);
        }
    }
    else
    {
        strcpy(pathname, name);
    }
    //printf("Name: %s\n", pathname);
    //return(1);
	if( 1 == do_stat(pathname,&file) )
    {
        printf("Error looking for file\n");
        return(1);
    }
	printf ("Full Name: %s\n", pathname);
    printf ("Inode Number: %d\n", file.st_ino);
	printf ("Mode: %d\n", file.st_mode);	
    printf ("User ID: %d\n", file.st_uid);
    printf ("Link Count: %d\n", file.st_nlink);
	printf ("Size: %d\n", file.st_size);
    printf ("Last Modified: %s\n", (char*)ctime(&file.st_atime) );
}
 
int do_stat(char *pathname, struct stat *file)
{
    int ino;
    MINODE* mip;
    if( 0 == strcmp(pathname, "/") )
    {
        ino = root->ino;
    }
    else
    {
	   ino = getino(device, pathname);
    }
    if(ino == 0)
        return (1);
    //ip = getInode(device, ino);
    mip = iget(device, ino);
    if(ip == NULL)
        return(1);
	file->st_ino = mip->ino;
	file->st_mode = mip->i_node.i_mode;
	file->st_nlink = mip->i_node.i_links_count;
    file->st_uid = mip->i_node.i_uid;
    file->st_gid = mip->i_node.i_gid;
    file->st_size = mip->i_node.i_size;
    file->st_blksize = BLOCK_SIZE;
    file->st_blocks = mip->i_node.i_blocks / (BLOCK_SIZE / 512);
    file->st_atime = mip->i_node.i_atime;
    //file->st_mtime = mip->i_node.i_mtime;
    //file->st_ctime = mip->i_node.i_ctime;
    return 0;
}

int my_chmod(int dev,int newMode, char* pathname)//in octal
{
    MINODE* mip;
    char pathnamed[256];
    //time_t s = time();
    if(pathname == NULL)
    {
        output("Must give a name");
        return(1);
    }
    else if(pathname[0] != '/')
    {
        strcpy(pathname, running->cwd->name);
        if( 0 == strcmp(pathnamed, "/") )
        {
            strcat(pathnamed, pathname);
        }
        else
        {
            strcat(pathnamed, "/");
            strcat(pathnamed, pathname);
        }
    }
    else
    {
        strcpy(pathnamed, pathname);
    }
	mip = iget(dev,getino(device,pathnamed));
	if(mip == NULL)
	{
		output("File doesnt exist");
		return -1;
	}
    
	mip->i_node.i_mode = newMode;		/* DIR and permissions */
	mip->dirty = 1;
	return 0;  
}

int my_touch(int dev, char *name)
{
	MINODE* mip;
    char pathname[256];
    //time_t s = time();
    if(name == NULL)
    {
        output("Must give a name");
        return(1);
    }
    else if(name[0] != '/')
    {
        strcpy(pathname, running->cwd->name);
        if( 0 == strcmp(pathname, "/") )
        {
            strcat(pathname, name);
        }
        else
        {
            strcat(pathname, "/");
            strcat(pathname, name);
        }
    }
    else
    {
        strcpy(pathname, name);
    }
	mip = iget(dev,getino(device,pathname));
	if(mip == NULL)
	{
		output("File doesnt exist");
		return -1;
	}
    
	mip->i_node.i_atime = time(NULL);
	mip->dirty = 1;
	return 0;  

}
write_dirty()
{
    int i;
    for(i = 0; i < NMINODES;i++)
    {
        if( Minode[i].dirty == 1 )
        {
            irelease(&Minode[i]);
        }
    }
}

int is_dir(MINODE* mip)
{
    int blk = 0;
    struct stat a;
    blk = mip->i_node.i_block[0];
    if( blk == 0 ) 
        return(0);
    do_stat(mip->name,&a);
    if(a.st_mode != 16877)
        return 0;
    return 1;
    
}








 
