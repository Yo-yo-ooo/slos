#include <inc/cpp/iosfwd>

void ostream::operator << (char *msg){
    printf("%s",msg);
}