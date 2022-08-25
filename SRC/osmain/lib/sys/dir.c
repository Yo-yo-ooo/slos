#include <inc/sys/dir.h>
#include <inc/lib.h>

#define MAX_PATH 1024
#ifndef DIRSIZ
#define DIRSIZ   14
#endif
struct direct
{
    ino_t d_ino;
    char d_name;
};


void dirwalk(char *dir, void (*fcn)(char *));

void fsize(char *name){
    struct Stat stbuf;

    if(stat(name, &stbuf) == -1){
        printf("fsize: can't access %s\n",name);
        return;
    }
    printf("%8ld %s\n", stbuf.st_size,name);
}

void dirwalk(char *dir, void (*fcn)(char *)){
    char name[MAX_PATH];
    Dirent *dp;
    DIR *dfd;

    if((dfd = opendir(dir)) == NULL){
        printf("dirwalk: can not open %s",dir);
        return;
    }
    while ((dp = readdir(dfd)) != NULL)
    {
        if(strcmp(dp->name, ".") == 0
        || strcmp(dp->name, "..") == 0)
            continue;
        if(strlen(dir) + strlen(dp->name) + 2 > sizeof(name)){
            printf("dirwalk: name %s%s too long", dir, dp->name);
        }else{
            (*fcn)(name);
        }
    }
    closedir(dfd);
}

DIR *opendir(char *dirname){
    int fd;
    struct Stat stbuf;
    DIR *dp;

    if((fd == open(dirname, O_RDONLY)) == -1
    || fstat(fd, &stbuf) == -1
    || (dp = (DIR *) malloc(sizeof(DIR))) == NULL){
        return NULL;
    }
    dp->fd = fd;
    return dp;
}

Dirent *readdir(DIR *dfd){
    struct direct dirbuf;
    static Dirent d;

    while (read(dfd->fd, (char *) &dirbuf, sizeof(dirbuf)))
    {
        /* code */
        if(dirbuf.d_ino == 0){
            continue;
        }
        d.ino = dirbuf.d_ino;
        strncpy(d.name, dirbuf.d_name, DIRSIZ);
        d.name[DIRSIZ] = '\0';
        return &d;
    }
    return NULL;
}

void closedir(DIR *dfd){
    if(dfd){
        close(dfd->fd);
        free(dfd);
    }
}