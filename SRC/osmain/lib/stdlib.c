#include <inc/stdlib.h>
#include <inc/lib.h>

int atoi(char *str){
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

void ltoa(long num, char* str, int radix)
{
    int i = 0;
	  int j = 0;
    long sum;
    unsigned long num1 = num;  //如果是负数求补码，必须将他的绝对值放在无符号位中在进行求反码
    char str1[33] = { 0 };
    if (num<0) {              //求出负数的补码
        num = -num;
        num1 = ~num;
        num1 += 1;
    }
    if (num == 0) {             
        str1[i] = '0';
        
        i++;
    }
    while(num1 !=0) {                      //进行进制运算
        sum = num1 % radix;
        str1[i] = (sum > 9) ? (sum - 10) + 'a' : sum + '0';
        num1 = num1 / radix;
        i++;
    }
    i--;
    
    for (i; i >= 0; i--) {               //逆序输出 
        str[i] = str1[j];
        j++;
    }
    
}

char *ultoa(unsigned long value, char *string, int radix)
{
    char tmp[33];
    char *tp = tmp;
    long i;
    unsigned long v = value;
    char *sp;

    if (radix > 36 || radix <= 1)
    {
        //__set_errno(EDOM);
        return 0;
    }


    while (v || tp == tmp)
    {
        i = v % radix;
        v = v / radix;
        if (i < 10)
        *tp++ = i+'0';
        else
        *tp++ = i + 'a' - 10;
    }
    if (string == 0)
        string = (char *)malloc((tp-tmp)+1);
    sp = string;

    while (tp > tmp)
        *sp++ = *--tp;
    *sp = 0;
    return string;
}

double atof(const char *str)
{
	double s=0.0;
 
	double d=10.0;
	int jishu=0;
 
	bool falg = false;
 
	while(*str==' ')
	{
		str++;
	}
 
	if(*str=='-')//记录数字正负
	{
		falg=true;
		str++;
	}
 
	if(!(*str>='0'&&*str<='9'))//如果一开始非数字则退出，返回0.0
		return s;
 
	while(*str>='0'&&*str<='9'&&*str!='.')//计算小数点前整数部分
	{
		s=s*10.0+*str-'0';
		str++;
	}
 
	if(*str=='.')//以后为小树部分
		str++;
 
	while(*str>='0'&&*str<='9')//计算小数部分
	{
		s=s+(*str-'0')/d;
		d*=10.0;
		str++;
	}
 
	if(*str=='e'||*str=='E')//考虑科学计数法
	{
		str++;
		if(*str=='+')
		{
			str++;
			while(*str>='0'&&*str<='9')
			{
				jishu=jishu*10+*str-'0';
				str++;
			}
			while(jishu>0)
			{
				s*=10;
				jishu--;
			}
		}
		if(*str=='-')
		{
			str++;
			while(*str>='0'&&*str<='9')
			{
				jishu=jishu*10+*str-'0';
				str++;
			}
			while(jishu>0)
			{
				s/=10;
				jishu--;
			}
		}
	}
 
    return s*(falg?-1.0:1.0);
}

long atol(const char *nptr)
{
    int c;
    long total = 0;
    int sign;
    while(isspace((int)(unsigned char)*nptr))//跳过前面的空格
        ++nptr;
    c = (int)(unsigned char)*nptr++;
    sign = c;
    if(c == '-' || c == '+')
        c = (int)(unsigned char) *nptr++;

    while(isdigit(c))
    {
        total = 10 * total + c- '0';
        c = (int)(unsigned char)*nptr++;
    }
    if(sign == '-')
        return -total;
    else
        return total;
}

/***************************
函数名:Bin2BCD
功能描述:把2进制转BCD值
参数：2进制值
返回：BCD值
***************************/
u_8 Bin2BCD( u_8 BinCode )
{
    return( ( ( (BinCode)/10 ) << 4 ) + ( (BinCode) %10 ));  
}

/***************************
函数名:Bcd2Bin
功能描述:把BCD值转2进制
参数：BCD值
返回：2进制值
***************************/
u_8 Bcd2Bin(u_8 BcdCode)
{
    return(((( BcdCode >> 4 ) & 0x0F ) * 10 ) + ( BcdCode & 0x0F ));  
}

div_t div(int num, int denom)
{

   div_t r;
   r.quot = num / denom;
   r.rem = num % denom;

   /*
      在我们普通PC（Intel架构系列的CPU）上
      可以正常运行。但是我们不知道其他的机器
      是怎么来处理整除和取余运算的，所以还是
      要写出来错误处理代码。
      被除数为正，余数为负，商加1，余数减除数。
      被除数为负，余数为正，商减1，余数加除数。
   */

    

   if (num >= 0 && r.rem < 0){
      ++r.quot;
      r.rem -= denom;
   }

   else if (num < 0 && r.rem > 0){
      --r.quot;
      r.rem += denom;
   }
   return (r);
}

ldiv_t ldiv(long int num, long int denom){
    ldiv_t r;
    r.quot = num / denom;
    r.rem = num % denom;

    /*
        在我们普通PC（Intel架构系列的CPU）上
        可以正常运行。但是我们不知道其他的机器
        是怎么来处理整除和取余运算的，所以还是
        要写出来错误处理代码。
        被除数为正，余数为负，商加1，余数减除数。
        被除数为负，余数为正，商减1，余数加除数。
    */

        

    if (num >= 0 && r.rem < 0){
        ++r.quot;
        r.rem -= denom;
    }

    else if (num < 0 && r.rem > 0){
        --r.quot;
        r.rem += denom;
    }
    return (r);
}