#include <inc/cpp/iosfwd>

void ostream::operator << (char *msg)const{
    printf("%s",msg);
    return* this;
}

void ostream::operator << (int value)const{
    printf("%d",value);
    return* this;
} 

void ostream::operator << (float d)const{
    printf("%f",d);
    return* this;
}

void ostream::operator << (double d)const{
    printf("%f",d);
    return* this;
}

void istream::operator<<()