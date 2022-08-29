#include <inc/stdio.h>
#include <inc/lib.h>

#define LOCALFMT 100

void scanf(char *fmt, ...){
    va_list ap;
    char *p, *sval;
    char localfmt[LOCALFMT];
    int c,i,*ival;
    unsigned *uval;
    double *dval;

    i = 0;
    va_start(ap,fmt);
    for(p = fmt; *p; p++){
        if(*p != '%'){
            putchar(*p);
            continue;
        }
        i = 0;
        localfmt[i++] = '%';
        while (*(p + 1) && !isalpha(*(p + 1)))
        {
            localfmt[i++] = *++p;
        }
        localfmt[i++] = *(p + 1);
        localfmt[i] = '\0';
        switch (*++p)
        {
        case 'd':
        case 'i':
            ival = va_arg(ap, int *);
            scanf(localfmt, ival);
            break;
        case 'x':
        case 'X':
        case 'u':
        case 'o':
            uval = va_arg(ap, unsigned *);
            scanf(localfmt, uval);
            break;
        case 'f':
            dval = va_arg(ap, double *);
            scanf(localfmt, dval);
            break;
        case 's':
            sval = va_arg(ap, char *);
            scanf(localfmt, sval);
            break;
        
        default:
            break;
        }
    }
    va_end(ap);
}