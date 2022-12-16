#ifndef _CTYPE_H
#define _CTYPE_H

#ifdef __cplusplus
extern "C" {
#endif

int isalnum(int c);
int isalpha(int c);
int iscntrl(int c);
int isdigit(int c);
int isgraph(int c);
int islower(int c);
int isprint(int c);
int isupper(char c);
int isspace(int c);
int isxdigit(int c);

#ifdef __cplusplus
}
#endif

#endif