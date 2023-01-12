#ifndef __STDLIB__
#define __STDLIB__

#include <inc/types.h>

int atoi(char *str);
char *itoa(int value,char *string,int radix);
void ltoa(long num, char* str, int radix);
char *ultoa(unsigned long value, char *string, int radix);
double atof(const char *str);
long atol(const char *nptr);

#endif