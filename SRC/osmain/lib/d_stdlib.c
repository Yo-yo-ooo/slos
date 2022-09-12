#include <inc/d_stdlib.h>
#include <inc/lib.h>

/*
* 文件: d_stdlib.c
* 介绍: 增加lib.h里的函数
*   
*/

unsigned long int next = 1;

int rand(void){
    next = next * 1103515245 + 12345;
    return (unsigned int)(next / 65536) % 32768;
}
void srand(unsigned int seed){
    next = seed;
}

double atof(const char *str){
    const char *p = str;
    int sign = 1;
    while (*p == ' ')++p;//忽略前置空格
    if (*p == '-')//考虑是否有符号位
    {
        sign = -1;
        ++p;
    }
    else if (*p == '+')
        ++p;
    int hasDot = 0,hasE = 0;
    double integerPart = 0.0,decimalPart = 0.0;
    //遇到'e'或'.'字符则退出循环,设置hasE和hasDot。
    for (; *p; ++p){
        if (isdigit(*p)) //若p指向的字符为数字则计算当前整数部分的值
            integerPart = 10 * integerPart + *p - '0';
        else if (*p == '.'){
            hasDot = 1;
            p++;
            break;
        }
        else if (*p == 'e' || *p == 'E'){
            hasE = 1;
            p++;
            break;
        }
        else  //如果遇到非法字符,则截取合法字符得到的数值,返回结果。
            return integerPart;
    }

//上一部分循环中断有三种情况,一是遍历完成,这种情况下一部分的循环会自动跳过；其次便是是遇到'.'或'e',两种hasE和hasDot只可能一个为真,若hasDot为真则计算小数部分,若hasE为真则计算指数部分。
    int decimalDigits = 1;
    int exponential = 0;    
    for (; *p; p++){
        if (hasDot && isdigit(*p))
            decimalPart += (*p - '0') / pow(10, decimalDigits++);
        else if (hasDot && (*p == 'e' || *p == 'E')) {
            integerPart += decimalPart;
            decimalPart = 0.0;
            hasE = 1;
            ++p;
            break;
        }
        else if (hasE && isdigit(*p))
            exponential = 10 * exponential + *p - '0';
        else break;
    }
//上一部分较难理解的就是else if (hasDot && (*p == 'e' || *p == 'E')) 这一特殊情况,对于合法的浮点数,出现'.'字符后,仍然有可能是科学计数法表示,但是出现'e'之后,指数部分不能为小数(这符合<string.h>对atof()的定义)。这种情况变量IntegerPart和decimalPart都是科学计数法的基数,因此有integerPart += decimalPart(这使得IntergerPart的命名可能欠妥,BasePart可能是一种好的选择)。
//上一部分循环结束一般情况下就能返回结果了,除非遇到前文所述的特殊情况，对于特殊情况需要继续计算指数。
    if (hasE && hasDot)
        for (; *p; p++)
            if (isdigit(*p))
                exponential = 10 * exponential + *p - '0';
    return sign * (integerPart * pow(10, exponential) + decimalPart);

}


enum state
{
	INVALID, //0
	VALID //1
};
enum state STATE = INVALID;//记录是合法访问的值还是非法访问的值
int atoi(const char* s)
{
	int flag;
	//assert(s != NULL);
	if (s == NULL)
		return 0;
	if (*s == '\0')
		return 0;
	//跳过空白字符
	while (isspace(*s))//是空白字符返回非0值 非空白字符不进入
	{
		s++;
	}
	//处理+-
	if (*s == '+')
	{
		flag = 1;
		s++;
	}
	else if (*s == '-')
	{
		flag = -1;
		s++;
	}
	//处理数字字符的转换
	long long  n = 0;
	while (isdigit(*s))
	{
		n = n * 10 + (*s - '0') * flag;
		if (n > INT_MAX || n < INT_MIN)
		{
			return 0;
		}
		s++;
	}
	//非数字字符或\0
	if (*s == '\0')
	{
		STATE = VALID;
		return (int)n;
	}
	else//非数字字符
	{
		STATE = INVALID;
		return (int)n;
	}                        
}

/*Qsort Function*/


int Cmp_qsort(void const* p1, void const* p2)//用户输入，
{
	int size1 = (*(int*)p1 - *(int*)p2);
	return size1;
}
 
//交换数据
void QSwap(char* base1, char* base2, int size)
{
	for (int i = 0; i < size; ++i)//按字节转换
	{
		char tmp = *base1;
		*base1 = *base2;
		*base2 = tmp;
		++base1;
		++base2;	
	}
}
 
//模拟实现
void _Quick_qsort(void const* base, int left, int right, int size, int(*Cmp_qsort)(void const* p1, void const* p2))
{
	if (left >= right)
	{
		return;
	}
 
	int begin = left;
	int end = right;
	int key = begin;//记录坑位的下标、
 
	while (begin < end)
	{
 
		while (begin < end && (Cmp_qsort((char*)base+ key*size, (char*)base + end * size) <= 0))
			--end;
 
		while (begin < end && (Cmp_qsort((char*)base+ key*size, (char*)base + begin * size) >= 0))
			++begin;
		QSwap((char*)base +begin * size, (char*)base+end*size, size);
 
	}
	QSwap((char*)base + begin * size, (char*)base + key * size, size);
 
	_Quick_qsort(base, left, begin - 1, size, Cmp_qsort);
	_Quick_qsort(base, begin + 1, right, size, Cmp_qsort);
 
}
 
 
//过渡一下
void qsort(void const* base, int len, int size,int(*Cmp_qsort)(void const *p1,void const *p2))
{
	_Quick_qsort(base, 0, len - 1, size, Cmp_qsort);//左右区间写入参数，
}
 
//打印
void QPrint(int* a, int n)
{
	for (int i = 0; i < n; ++i)
	{
		printf("%d ", a[i]);
	}
}

#define YES     1
#define NO      0

int htoi(char s[]){
    int hexdigit,i,inhex,n;

    i = 0;
    if(s[i] == '0'){
        ++i;
        if(s[i] == 'x' || s[i] == 'X')
            ++i;
    }
    n = 0;
    inhex = YES;
    for(; inhex == YES; ++i){
        if(s[i] >= '0' && s[i] <= '9')
            hexdigit = s[i] - '0';
        else if(s[i] >= 'a' && s[i] <= 'f')
            hexdigit = s[i] - 'a' + 10;
        else if(s[i] >= 'A' && s[i] <= 'F')
            hexdigit = s[i] - 'A' + 10;
        else
            inhex = NO;
        if(inhex == YES)
            n = 16 * n + hexdigit;
    }
    return n;
}

void* bsearch (const void* key, const void* base,
               size_t num, size_t size,
               int (*compar)(const void*,const void*)) {
    size_t low = 0;
    size_t high = num-1;
    size_t mid;
    while (low <= high) {
        mid = (low + high) >> 1;
        if (compar(key, (char *)base + mid * size) == 0) {
            break;
        }
        else if (compar(key, (char *)base + mid * size) < 0) {
            high = mid-1;
        }
        else {
            low = mid+1;
        }
    }

    if (low <= high) {
        return (char *)base + mid * size;
    }

    return;
}

div_t div(int num, int denom){
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

ldiv_t ldiv(long num, long denom){
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