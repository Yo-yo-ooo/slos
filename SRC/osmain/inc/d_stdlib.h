#ifndef _D_STDLIB_H
#define _D_STDLIB_H

#include <inc/lib.h>

/*
* This File is for Skyline System stdlib Library
* ----------------------------------------------
* Object: Done For lib.h C stdlib.h Library
*/

typedef struct {
    int quot;
    int rem;
} div_t;

typedef struct {
    long quot;
    long rem;
} ldiv_t;

int rand(void);
void srand(unsigned int seed);
double atof(char s[]);
int atoi(const char* s);
char* itoa(int num, char* buffer, int base);
void qsort(void const* base, int len, int size,int(*Cmp_qsort)(void const *p1,void const *p2));
void QPrint(int* a, int n);
int htoi(char s[]);
void* bsearch (const void* key, const void* base,size_t num, size_t size,int (*compar)(const void*,const void*));
div_t div(int num, int denom);
ldiv_t ldiv(long num, long denom);
char *ftoa(double number,int ndigit,char *buf);
char *ultoa(unsigned long value, char *string, int radix);

#endif