#include <inc/stdlib.h>
#include <inc/lib.h>

int atoi(char *str)
{
    return strtol(str, NULL, 10);
}

char *itoa(int value,char *string,int radix)
{
    char zm[37]="0123456789abcdefghijklmnopqrstuvwxyz";
    char aa[100]={0};
  
    int sum=value;
    char *cp=string;
    int i=0;
    
    if(radix<2||radix>36)//增加了对错误的检测
    {
        printf("error: invalid radix\n");
        return string;
    }
  
    if(value<0)
    {
        printf("error data!\n");
        return string;
    }
    
  
    while(sum>0)
    {
        aa[i++]=zm[sum%radix];
        sum/=radix;
    }
  
    for(int j=i-1;j>=0;j--)
    {
        *cp++=aa[j];
    }
    *cp='\0';
    return string;
}