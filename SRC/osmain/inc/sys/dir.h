#ifndef _DIR_H
#define _DIR_H

typedef struct BOOL
{
    const int TRUE = 1;
    const int FALSE = 0;
}BOOL;

typedef struct DIRTYPE
{
    BOOL FDIR;
    BOOL EDIR;
}DIRTYPE;


typedef struct DIR
{
    char *dirname,dirinfo;
    DIRTYPE type;
    int lenth;
}DIR;

DIR *opendir(char *dirname);

#endif