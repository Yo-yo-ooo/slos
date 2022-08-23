#include <inc/cpp/iosfwd>
#include <inc/stdio.h>

void ostream::operator << (char *msg)const{
    printf("%s",msg);
     
}

void ostream::operator << (int value)const{
    printf("%d",value);
     
} 

void ostream::operator << (float d)const{
    printf("%f",d);
     
}

void ostream::operator << (double d)const{
    printf("%f",d);
     
}

void istream::operator << (char *a)const{
    //帮我实现
     
}

void istream::operator << (String str)const{
    //帮我实现
     
}

void istream::operator >> (char *a)const{
     
}

void istream::operator >> (String str)const{
     
}