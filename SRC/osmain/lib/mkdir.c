#include "inc/lib.h"

int mkfile(char *name){
    if(strlen(name) > 500){
        return -1;
    }

    
    return open(name,(O_WRONLY | O_CREAT));
}

int mkdir(char *fn){
    mkfile(fn);
}