#include <inc/lib.h>

void umain(int argc, char **argv)
{
    int r;
    char *filename;
    char pathbuf[MAXPATH];
    pathbuf[0] = '\0';
    if (argc != 2)
    {
        bprintf("usage: touch filename\n");
        PAUSE
        return;
    }
    filename = argv[1];
    if (*filename != '/')
        getcwd(pathbuf, MAXPATH);
    strcat(pathbuf, filename);
    if ((r = open(pathbuf, O_CREAT)) < 0)
        bprintf("%s error : %e\n", argv[0], r);
    close(r);
    PAUSE
}