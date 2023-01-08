#include <inc/lib.h>

void umain(int argc, char **argv)
{
    char path[200];
    if(argc > 1)
        bprintf("%s : too many arguments\n",argv[0]);
    else
        bprintf("%s\n",getcwd(path,200));
}