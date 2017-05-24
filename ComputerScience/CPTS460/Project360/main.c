//CPTS 360 Final Project
//Alex Hortin
//Daniel Rodgers
//Nov 2007
#include "include.c"
void init(char* name)
{
    //initialize the simulator system's data structures:
    /*MOUNT mountTable[10];
    MINODE Minode[100];
    OFT oft[100];
    PROC proc[10];*/
    mount_root(name);
           //mount the rootdevice;  e.g. default to /dev/fd0
           //Run porc[0] as the current process P0  with  cwd = /;
}
token_arg(char* pathname)
{
    char* tp;
    int counter = 0;
    tp = strtok(pathname, " "); 
    while( tp != NULL)
    {
        argue[counter] = tp;
        counter++;
        tp = strtok(NULL, " ");
    }
    argue[counter] = NULL;
}
main(int argc, char *argv[])
{
    int counter = 0;
    MINODE* wtf;
    char command[256];
    //char dead_command[256];
    if (argc < 2)
    {
        init(NULL);
    }
    else
    {
        init(argv[1]);
    }
/*
    wtf = iget(device,30);
    printf("BALLOC %d\n", balloc(device));
printf("BALLOC %d\n", balloc(device));
printf("BALLOC %d\n", balloc(device));
printf("BALLOC %d\n", balloc(device));

        printf("iALLOC %d\n", ialloc(device));
printf("iALLOC %d\n", ialloc(device));
printf("iALLOC %d\n", ialloc(device));
printf("iALLOC %d\n", ialloc(device));
   exit(1);*/
    while (1)
    {
        argue[0] = NULL;
        while( argue[0] == NULL)
        {
            printf("[AWESOM-0 4000: CLI]#");
            gets(command);
            printf("\n");
            token_arg(command);
        }
    
        if ( 0==strcmp("ls",argue[0]) )
            my_ls(argue[1]);
        else if (0 == strcmp("pwd", argue[0]))
            my_pwd();
        else if (0 == strcmp("cd", argue[0]))
        {
            if( 1 == my_cd(argue[1]) )
            {
               output("ERROR: FILE NOT FOUND/A_DIRECTORY");
            }
        }
        else if (0 == strcmp("stat", argue[0]))
        {
            my_stat(device, argue[1]);
        }
        else if (0 == strcmp("exit", argue[0]) || 0 == strcmp("quit", argue[0] ))
        {
            output("LAME");
            write_dirty();
            exit(1);
        }
        else if (0 == strcmp("menu", argue[0] ))
        {
            printf("******************** Menu *******************\n");
            printf("ls        cd        rmdir     create    pwd\n");
            printf("stat      touch     mkdir\n");

        }
        else if(0 == strcmp("mkdir", argue[0] ))
        {
            my_mkdir(device, argue[1]);
        }
        else if(0 == strcmp("touch", argue[0] ))
        {
            my_touch(device, argue[1]);

        }
		 else if(0 == strcmp("create", argue[0] ))
        {
            my_create(device, argue[1]);

        }
		else if(0 == strcmp("chmod", argue[0] ))
        {
            my_chmod(device,(int)argue[1], argue[2]);

        }
		else if(0 == strcmp("rmdir", argue[0] ))
        {
            my_rmdir(device,argue[1]);
        }
        else
            output("AMESOM-0 is not programed to do that\n");
    }
    close(device);
}
