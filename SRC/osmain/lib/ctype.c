#include <inc/ctype.h>

int isalnum(int c){
    if ( (c>='a' && c<='z') || (c>='A' && c<='Z') || (c>='0' && c<='9') ) return 8;

    return 0;
}
int isalpha(int c){
    if ( (c>='a' && c<='z') || (c>='A' && c<='Z') ) return 1024;

    return 0;
}
int iscntrl(int c){
    return (unsigned int)c < 32u  ||  c == 127;
}
int isdigit(int c){
    if ( (c>='a' && c<='z') || (c>='A' && c<='Z') ) return 1024;

    return 0;
}
int isgraph(int c){
    return (unsigned int)(c - '!') < 127u - '!';
}
int islower(int c){
    if (c>='a' && c<='z') return 512;

    return 0;
}
int isprint(int c){
    return (unsigned int)(c - ' ') < 127u - ' ';
}
int isspace(int c)
{
    if(c == '\t'|| c == '\n'|| c == ' ')
        return 1;
    else
        return 0;
}
int ispunct(int c){
    return isprint(c)  &&  !isalnum (c)  &&  !isspace (c);
}
int isupper(int c){
  if (c>='A' && c<='Z') return 256;

  return 0;
}
int my_isxdigit(int c){
    return (unsigned int)( c         - '0') < 10u  ||
           (unsigned int)((c | 0x20) - 'a') <  6u;
}