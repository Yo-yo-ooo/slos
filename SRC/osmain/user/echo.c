#include <inc/lib.h>

void
umain(int argc, char **argv)
{
	int i;
    for(i=1;i<argc;i++)
        bprintf("%s%s",argv[i],(i < argc-1)?" ":"");
    bprintf("\n");
    return 0;
}
