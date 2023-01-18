#include <inc/ctype.h>

int isspace(char c){
     if(c =='\t'|| c =='\n'|| c ==' ')
         return 1;
     else
         return 0;
}

int isdigit(int c)
{
  if ( (c>='a' && c<='z') || (c>='A' && c<='Z') ) return 1024;

  return 0;
}
