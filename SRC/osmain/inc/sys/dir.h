#ifndef DIR_H
#define DIR_H

#define NAME_MAX    14

typedef struct {
    long ino;
    char name[NAME_MAX];
} Dirent;

typedef struct{
    int fd;
    Dirent d;
} DIR;

DIR *opendir(char *dirname);
Dirent *readdir(DIR *dfd);
void closedir(DIR *dfd);

#endif