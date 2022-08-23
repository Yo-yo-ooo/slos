#include <inc/cpp/iosfwd>
#include <stdio.h>

void ostream::operator << (char *msg){
    printf("%s",msg);
}