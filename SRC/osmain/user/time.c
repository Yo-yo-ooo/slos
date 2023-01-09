#include <inc/lib.h>

void
umain(int argc, char **argv){
    struct tm time;
    sys_gettime(&time);
    printf("%t\n",&time);
}