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

double atof(char s[]) /*convert string s to floating point*//* mjm: was atof1 */
{
	char *s1;
	char *s2;
	double val,power;
	int i,sign,esin,exp;

	s1 = s;
	s2 = s;
	while(*s2 != '\0')
		switch (*s2) {
			case ' ' :
			case '\015' :
			case '\012' :
			case '\t':
			s2++;
			break;
			case 'E':
			*s1++ = 'e';
			s2++;
			break;
			default:
			*s1++ = *s2++;
		}
	*s1 = '\0';
	i=0;
	sign = 1;
	if(s[i] == '+' || s[i] == '-')
		sign = (s[i++] == '+') ? 1 : -1 ;
	for(val = 0;s[i] >= '0' && s[i] <= '9';i++)
		val = 10 * val + s[i] - '0';
	if(s[i] == '.')
	{
		i++;
		for(power = 1;s[i] >= '0' && s[i] <= '9'; i++)
		{
			val = val * 10 + s[i] - '0';
			power *= 10;
		}
		val /= power;
	}
	if(s[i] == 'e')
	{
		i++;
		esin = 1;
		if(s[i] == '+' || s[i] == '-')
			esin = (s[i++] == '+') ? 1 : -1;
		for(exp = 0;s[i] >= '0' && s[i] <= '9';i++)
			exp = 10 * exp + s[i] - '0';
		power = 1;
		for(i=0;i<exp;i++)
			power *= 10;
		val = (esin == -1) ? val/power : val * power ;
	}
	return(sign * val);
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

char* itoa(int num, char* buffer, int base){
	int curr = 0;
 
    if (num == 0) {
        // Base case
        buffer[curr++] = '0';
        buffer[curr] = '\0';
        return buffer;
    }
 
    int num_digits = 0;
 
    if (num < 0) {
        if (base == 10) {
            num_digits ++;
            buffer[curr] = '-';
            curr ++;
            // Make it positive and finally add the minus sign
            num *= -1;
        }
        else
            // Unsupported base. Return NULL
            return NULL;
    }
 
    num_digits += (int)floor(log(num) / log(base)) + 1;
 
    // Go through the digits one by one
    // from left to right
    while (curr < num_digits) {
        // Get the base value. For example, 10^2 = 1000, for the third digit
        int base_val = (int) pow(base, num_digits-1-curr);
 
        // Get the numerical value
        int num_val = num / base_val;
 
        char value = num_val + '0';
        buffer[curr] = value;
 
        curr ++;
        num -= base_val * num_val;
    }
    buffer[curr] = '\0';
    return buffer;
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

char *ftoa(double number,int ndigit,char *buf)
{
    long int_part;
	double float_part;
	char str_int[32];
	char str_float[32];
	memset(str_int,0,32);
	memset(str_float,0,32);
	int_part = (long)number;
	float_part = number - int_part;
	// 整数部分处理
	itoa(int_part,str_int,10);
	// 小数部分处理
	if(ndigit>0)
	{
		float_part =fabs(pow(10,ndigit)*float_part);
		itoa((long)float_part,str_float,10);
	}
	int i = strlen(str_int);
	str_int[i] = '.';
	strcat(str_int,str_float);
	strcpy(buf,str_int);
	return buf;
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
		__set_errno(EDOM);
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