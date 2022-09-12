#include <inc/lib.h>
#include <inc/sys/bit.h>

unsigned getbits(unsigned x, int p, int n, unsigned y){
    return x & ~(~(~0 << n)) << (p + 1 - n) |
        (y &  ~(~0 << n)) << (p + 1 - n);
}

unsigned invert(unsigned x, int p, int n){
    return x ^ (~(~0 << n) << (p + 1 - n));
}

unsigned rightrot(unsigned x,int n){
    int wordlenth(void);
    int ribit;

    while(n-- > 0){
        ribit = (x & 1) << (wordlenth() - 1);
        x = x >> 1;
        x = x | ribit;
    }
    return x;
}

int wordlenth(void){
    int i;
    unsigned v = (unsigned) ~0;

    for(i = 1; (v = v >> 1) > 0; i++)
        ;
    return i;
}

int bitcount(unsigned x){
    int b;

    for(b = 0; x != 0; x &= x-1)
        ++b;
    return b;
}