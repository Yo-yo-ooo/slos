#include <inc/cpp/iosfwd>

void outstream::operator << (char *msg)const{
    printf("%s",msg);
    return* this;
}

void outstream::operator << (int value)const{
    printf("%d",value);
    return* this;
} 

void outstream::operator << (float d)const{
    printf("%f",d);
    return* this;
}

void outstream::operator << (double d)const{
    printf("%f",d);
    return* this;
}