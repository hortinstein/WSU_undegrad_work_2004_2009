/*////////////////////////////////////////////////////////////////////////////////////////
//hortinshelltype.h
//
//This is my own personal type.h so I would not have to modify the code we were given.
//All data structures contained are my own 
//
////////////////////////////////////////////////////////////////////////////////////////*/

typedef struct user
{
 
	char uname[16];
	char pword[16];
	int gid;
	int uid;
	char fullname[32];
	char homedir[32];
	char prog[15];

} USER;
