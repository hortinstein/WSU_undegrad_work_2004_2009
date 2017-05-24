
void mount_root(char* name)
{
    int fd;
    int counter = 0;
    fd = open(name, O_RDWR);
    if(fd == 0)
    {
        printf("Opening Default\n");
        fd = open("dev/fd0", O_RDONLY);
        name = "dev/fd0\0";
    }
    if(fd == 0)
    {
        printf("Could not open root");
        exit(1);
    }

    for(counter = 0; counter < NMINODES; counter++)
    {
        Minode[counter].refCount = 0;
    }



    lseek(fd, (long)(BLOCK_SIZE * 1), 0);
    read(fd, rbuf, BLOCK_SIZE);
    sp = (SUPER *)rbuf;
    if( sp->s_magic != 0xEF53 )
    {
        printf("Error, not a EXT2 file system\n");
        exit(1);
    }
    

    printf("///////SuperBlock///////\n");
    printf("Inode Count: %d\n", sp->s_inodes_count);
    printf("Block Count: %d\n", sp->s_blocks_count);
    printf("R_Block Count: %d\n", sp->s_r_blocks_count);
    printf("Free Blocks Count: %d\n", sp->s_free_blocks_count);
    printf("Free Inodes Count: %d\n", sp->s_free_inodes_count);
    printf("Log Block Count: %d\n", sp->s_log_block_size);
    printf("First Data Block: %d\n", sp->s_first_data_block);
    printf("Inode Per Group: %d\n", sp->s_inodes_per_group);
lseek(fd, (long)(BLOCK_SIZE * 2), 0);
    read(fd, rbuf, BLOCK_SIZE);
    gp = (GD *)rbuf;
    printf("\n///////GroupBlock///////\n");
    printf("Block Bitmap: %d\n", gp->bg_block_bitmap);
    printf("Inode Bitmap: %d\n", gp->bg_inode_bitmap );
    printf("Inode Table: %d\n", gp->bg_inode_table);
    printf("Free Blocks Count: %d\n", gp->bg_free_blocks_count);
    printf("Free Blocks Count: %d\n", gp->bg_free_inodes_count);
    printf("Dir Count: %d\n", gp->bg_used_dirs_count);
    inode_start = gp->bg_inode_table;
    printf("Inode Start: %d\n", inode_start);

/*
    mountTable[0].ninodes = sp->s_inodes_count;
    mountTable[0].nblocks = sp->s_blocks_count;
    mountTable[0].dev = 0;
    mountTable[0].busy = 0;   
    mountTable[0].mounted_inode = &Minode[0];
    strcpy(mountTable[0].name, name); 
    strcpy(mountTable[0].mount_name, "/\0");
*/
    lseek(fd, (long)(BLOCK_SIZE * gp->bg_inode_table), 0);
    read(fd, rbuf, BLOCK_SIZE);
    ip = (INODE*)rbuf + 1;
    Minode[0].i_node = *ip;               // disk inode
    Minode[0].dev = 0;
    Minode[0].ino = 2;
    Minode[0].refCount = 1;
    Minode[0].dirty = 0;
    Minode[0].mounted = 0;
    Minode[0].mountptr = &mountTable[0];
    strcpy(Minode[0].name, "/");           // name string of file

    device = fd;
    running = &proc[0];
    running->cwd = &Minode[0]; 
/*
    MINODE tp;
    tp.i_node = *ip;               // disk inode
    tp.dev = 0;
    tp.ino = 2;
    tp.refCount = 1;
    tp.dirty = 0;
    tp.mounted = 0;
    tp.mountptr = &mountTable[0];
    strcpy(tp.name, "/"); */
    root = &Minode[0];
    
}
