#ifndef _D_STDLIB_H
#define _D_STDLIB_H

/*
* This File is for Skyline System stdlib Library
* ----------------------------------------------
* Object: Done For lib.h C stdlib.h Library
*/
int rand(void);
void srand(unsigned int seed);
double atof(const char *str);
int atoi(const char* s);
void qsort(void const* base, int len, int size,int(*Cmp_qsort)(void const *p1,void const *p2));
void QPrint(int* a, int n);
int htoi(char s[]);

#endif