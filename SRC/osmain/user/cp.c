#include <inc/lib.h>

#define PERMS 0666

void error(char *fmt,...){
    va_list args;

    va_start(args,fmt);
    fprintf(stderr,"error: ");
    vfprintf(stderr,fmt,args);
    fprintf(stderr,"\n");
    va_end(args);
    exit();
}

void
umain(int argc, char **argv)
{
    int f1,f2,n;
    char buf[BUFSIZ];

    if(argc != 3){
        printf("Usage: cp from to\n");
        exit();
    }
    if((f1 = open(argv[1],O_RDONLY)) == -1)
        printf("cp: can't open %s\n",argv[1]);
    if((f2 = creat(argv[2], PERMS)) == -1)
        printf("cp: can't creat %s,mode %03o\n",argv[2],PERMS);
    while ((n = read(f1, buf, BUFSIZ)) > 0){
        if(write(f2,buf,n) != n){
            printf("cp: write error on file %s\n",argv[2]);
        }
    }
    return;
}