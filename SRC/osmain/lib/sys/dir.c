#include <inc/sys/dir.h>
#include <inc/lib.h>

struct FILEINFO
{
    unsigned char name[8], ext[3], type;
    char reserve[10];
    unsigned short time, date, clustno;
    unsigned int size;
};

DIR *opendir(char *dirname){
    
}