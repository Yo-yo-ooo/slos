#include <inc/stdio.h>
#include <inc/stdlib.h>			//为了使用库函数atof
#include <inc/math.h>			//使用sin, exp, pow等数学函数
#include <inc/string.h>			//使用strcmp, strlen等字符串函数

//extern NUMBER;
#define		NUMBER		'0'
#define		NAME		'n'

int getop(char s[])		//获取下一个运算符或操作数
{
	int i;
	int c;

	while((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	i = 0;
	if(c != '-' && !islower(c) && !isdigit(c) && c != '.')	//判断是否属于这四种情况，如不是，下面分别对这四种情况处理
		return c;		//当是运算符时，返回此运算符的ASCII值
	if(c == '-')
		if(isdigit(c = getch()) || c == '.')
			s[++i] = c;
		else
		{
			if(c != EOF)
				ungetch(c);
			return '-';
		}
	if(islower(c))
	{
		while(islower(s[++i] = c = getch()))
			;
		s[i] = '\0';
		if(c != EOF)
			ungetch(c);
		if(strlen(s) > 1)
			return NAME;
		else
			return s[0];   //错误：return c; 例：s = "v "，则
                                             //返回空格，而本意是返回v 
	}
	if(isdigit(c))
		while(isdigit(s[++i] = c = getch()))	//收集整数部分
			;
	if(c == '.')
		while(isdigit(s[++i] = c = getch()))	//收集小数部分
			;
	s[i] = '\0';
	if(c != EOF)
		ungetch(c);

	return NUMBER;		//当是操作数时，返回NUMBER，标识这种情况
}

#define		BUFSIZE		100		//缓冲区的最大长度

//int buf[BUFSIZE];				//这样可以正确处理压回EOF(-1)及其他任何负数的情况
char buf[BUFSIZE];				//用于ungetch函数的缓冲区
int bufp = 0;					//buf中下一个空闲位置

int getch()						//取一个字符(可能是要压回的字符)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)				//把字符压回到输入(缓冲区)中
{
	if(bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

#define		MAXOP		100	//操作数或运算符的最大长度（待处理字符串的最大长度）
#define		NUMBER		'0'	//标识找到一个数
#define		NAME		'n' //标示找到一个数学函数

void push(double );
double pop();
//void printStack(double []);
void clear();
void mathfnc(char []);

//extern double val[];		//如果声明为extern val[]; 则报错：变量val被重定义
//extern sp;

//逆波兰计算器
void umain(int argc, char **argv)
{
	int type;
	double op2;
	double op1;
	//double tmp;
	char s[MAXOP];

    printf("This is the inverse Polish calculator(V0.75c),\nPress 'q' to quit.\n");

	while((type = getop(s)) != EOF)
	{
		switch(type)
		{
		case NUMBER:		//当待处理字符串是数值字符串时，将其转换，并压栈
			push(atof(s));
			break;

		case '+':
			push(pop() + pop());
			break;

		case '*':
			push(pop() * pop());
			break;

		case '-':
			op2 = pop();
			push(pop() - op2);	//push(pop() - pop());是错误的，虽然算法运算符中操作数的结合方式是从左到右
								//但是不能确定push参数中左边的pop函数一定比右边的pop函数先执行
			break;

		case '/':
			op2 = pop();
			if(op2 != 0.0)
				push(pop() / op2);
			else
			{
				printf("error: divide 0.0!\n");
				return -1;
			}
			break;

		case '%':
			op2 = pop();
			if(op2 != 0.0)
				push(fmod(pop(), op2));
			else
				printf("error: mod 0.0!\n");
			break;

		case '\n':		//当键入换行符时，打印输出栈顶元素
			/*if(sp > 0)
				printStack(val);
			else
				printf("error: stack empty!\n");
			*/
			printf("the result = %.8g\n", pop());
			break;

		case 'p':		//不出栈的情况下，打印栈顶元素
			op2 = pop();
			printf("the top element of stack = %f\n", op2);
			push(op2);
			break;

		case 'd':		//复制栈顶元素
			op2 = pop();
			//tmp = op2;
			//printf("the duplication of top element = %f\n", op2);
			push(op2);
			push(op2);
			printf("the duplication of top element = %f\n", op2);
			break;

		/*case 'S':
			push(sin(pop()));
			break;

		case 'E':
			push(exp(pop()));
			break;

		case 'P':
			op2 = pop();
			push(pow(pop(), op2));
			break;
		*/

		case NAME:		//处理数学函数分支，这样比上面分别用每个命令来定义一个函数要通用，并容易扩展
			mathfnc(s);
			break;

		case 's':		//交换栈顶元素
			op2 = pop();
			op1 = pop();
			push(op2);
			push(op1);
			break;

		case 'c':		//清空堆栈
			clear();
			break;
        case 'q':
            exit();
            break;
		default:
			printf("error: unknown command %s\n", s);
			break;

		}
	}

	return 0;
}

#define		MAXVAL		100		//栈val的最大深度

int sp = 0;						//栈中的下一个空闲的位置
double val[MAXVAL];				//值栈

void push(double f)				//把f压入值栈中
{
	if(sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

double pop()					//从值栈中弹出并返回栈顶的值
{
	if(sp > 0)
		return val[--sp];
	else
	{
		printf("error: stack empty, can't pop\n");
		return 0.0;
	}
}

/*void printStack(double* val)
{
	printf("top of stack = %f\n", val[sp-1]);
}
*/

void clear()					//清空值栈
{
	sp = 0;

	return;

}

void mathfnc(char s[])			//数学函数处理的通用接口
{
	double op2;

	if(strcmp(s, "sin") == 0)
		push(sin(pop()));
	else if(strcmp(s, "cos") == 0)
		push(cos(pop()));
	else if(strcmp(s, "exp") == 0)
		push(exp(pop()));
	else if(strcmp(s, "pow") == 0)
	{
		op2 = pop();
		push(pow(pop(), op2));
	}
	else
		printf("error: %s not supported!\n", s);
	
}