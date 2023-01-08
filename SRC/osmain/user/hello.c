#include <inc/lib.h>

void umain(int argc, char **argv)
{
	bprintf("hello world\n");
	char *buf = readline("Input:");
	bprintf("%s",buf);
	getchar();
}

