/***********************************************************************
 crt0.c : main0(s) called from u.s, where s = oigianl command string
          tokenlize s into char *argv[ ] and call main(argc, argv).
 
 token() breaks up a string into argc of tokens, pointed by argv[]
**********************************************************************/

int argc;
char *argv[32];

int token(line) char *line;
{
  int i;
  char *cp;
  cp = line;
  argc = 0;
  
  while (*cp != 0){
       while (*cp == ' ') *cp++ = 0;        
       if (*cp != 0)
           argv[argc++] = cp;         
       while (*cp != ' ' && *cp != 0) cp++;                  
       if (*cp != 0)   
           *cp = 0;                   
       else 
            break; 
       cp++;
  }
  argv[argc] = 0;
}
 
int main0(s) char *s;
{
  token(s);
  main(argc, argv);
}


