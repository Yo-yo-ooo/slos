#include <inc/math.h>
/*
FILE:math.c

*/

double static sq2p1	 =2.414213562373095048802e0;
static double sq2m1	 = .414213562373095048802e0;
static double pio2	 =1.570796326794896619231e0;
static double pio4	 = .785398163397448309615e0;
static double p4	 = .161536412982230228262e2;
static double p3	 = .26842548195503973794141e3;
static double p2	 = .11530293515404850115428136e4;
static double p1	 = .178040631643319697105464587e4;
static double p0	 = .89678597403663861959987488e3;
static double q4	 = .5895697050844462222791e2;
static double q3	 = .536265374031215315104235e3;
static double q2	 = .16667838148816337184521798e4;
static double q1	 = .207933497444540981287275926e4;
static double q0	 = .89678597403663861962481162e3;


/*
	atan makes its argument positive and
	calls the inner routine satan.
*/

double
atan(double x)
{
	double satan();

	if(x>0)
		return(satan(x));
	else
		return(-satan(-x));
}


/*
	atan2 discovers what quadrant the angle
	is in and calls atan.
*/

double
atan2(double x,double y)
{
	double satan();

	if((x+y)==x)
		if(x >= 0.) return(pio2);
		else return(-pio2);
	else if(y <0.)
		if(x >= 0.)
			return(pio2+pio2 - satan(-x/y));
		else
			return(-pio2-pio2 + satan(x/y));
	else if(x>0)
		return(satan(x/y));
	else
		return(-satan(-x/y));
}

/*
	satan reduces its argument (known to be positive)
	to the range [0,0.414...] and calls xatan.
*/

double satan(double x)
{
	double	xatan();

	if(x < sq2m1)
		return(xatan(x));
	else if(x > sq2p1)
		return(pio2 - xatan(1.0/x));
	else
		return(pio4 + xatan((x-1.0)/(x+1.0)));
}

/*
	xatan evaluates a series valid in the
	range [-0.414...,+0.414...].
*/

double xatan(double x)
{
	double argsq;
	double value;

	argsq = x*x;
	value = ((((p4*argsq + p3)*argsq + p2)*argsq + p1)*argsq + p0);
	value = value/(((((argsq + q4)*argsq + q3)*argsq + q2)*argsq + q1)*argsq + q0);
	return(value*x);
}

double pow(double x, double y){
	double value = 1;
    int i = 1;
    if(y ==0)
    {
        value = 1;
    }
    else
    {
        while(i++<= y)
        {
            value *= x;
        }
    }
    return value;
}


double fabs(double x){
	*( ( (int *) & x) + 1) &=0x7FFFFFFF;
  	return x;
}

const double TINY_VALUE = 1e-10;  //计算精度

double sin(double x){   
    double n = x,sum=0;
    int i = 1;
    do
    {
        sum += n;
        i++;
        n = -n * x*x / (2 * i - 1) / (2 * i - 2);

    } while (fabs(n)>=TINY_VALUE);
    return sum;
}

double cos(double x){
	int t,q=1;
 	double term,factorial=1.0,sum2=1,sxm,sum1=0;
    for(t=2;;t++){
        factorial=factorial*t;//控制阶乘
        if(t%2==0){
            sum1=sum2;
            q=q*(-1);
            sxm=fabs(pow(x,t));//取绝对值后的x次方    
            term=sxm/factorial;
            sum2=q*term+sum2;
        }
        if(fabs(sum2-sum1)<=1e-5)//定义前后两个数，控制输出精度
            break;
    }
    return sum2;
}

double tan(double x)
{
	return(sin(x)/cos(x));
}

double
asin(double x){

	double sign, temp;

	sign = 1.;
	if(x <0){
		x = -x;
		sign = -1.;
	}

	if(x > 1.){
		return(0.);
	}

	temp = sqrt(1. - x*x);
	if(x > 0.7)
		temp = pio2 - atan(temp/x);
	else
		temp = atan(x/temp);

	return(sign*temp);
}

double
acos(double x){

	if((x > 1.) || (x < -1.)){
		return(0.);
	}

	return(pio2 - asin(x));
}

double
fmod(double x, double y)
{
	extern double modf();
	double d;

	if (y == 0.0)
		return (x);

	modf(x/y, &d);
	return (x - d * y);
}

typedef struct{
   unsigned int mantissal:32;
   unsigned int mantissah:20;
   unsigned int exponent:11;
   unsigned int sign:1;
}double_t;//这个结构体在IEEE.h定义。

double modf(double x, double *ip){

   double_t * z = (double_t *)&x;
   double_t * iptr = (double_t *)ip;

   int j0;

   unsigned int i;

   j0 = z->exponent - 0x3ff;  /* exponent of x */ 

   if(j0<20)

   {/* integer part in high x */

      if(j0<0)

      {                  /* |x|<1 */

        *ip = 0.0;

        iptr->sign = z->sign;

        return x;

      }

      else

      {

        if ( z->mantissah == 0 && z->mantissal == 0 )

        {

           *ip = x;

           return 0.0;

        }

        i = (0x000fffff)>>j0;

        iptr->sign = z->sign;

        iptr->exponent = z->exponent;

        iptr->mantissah = z->mantissah&(~i);

        iptr->mantissal = 0;

        if ( x == *ip )

        {

           x = 0.0;

           z->sign = iptr->sign;

           return x;

        }         

              return x - *ip;       

      }

   }

   	else if (j0>51){             /* no fraction part */
      	*ip = x;

      	if ( isnan(x) || isinf(x) )

        	return x;

      	x = 0.0;

      	z->sign = iptr->sign;

      	return x;
	}

   else{                        /* fraction part in low x */
      i = ((unsigned)(0xffffffff))>>(j0-20);
      iptr->sign = z->sign;
      iptr->exponent = z->exponent;
      iptr->mantissah = z->mantissah;
      iptr->mantissal = z->mantissal&(~i);
      if ( x == *ip ){
        x = 0.0;
        z->sign = iptr->sign;
        return x;

    	}

      return x - *ip;       
   }

}

//下面是两个要用到的函数

int isnan(double d){

   union{
      unsigned long long l;
      double d;
   } u;
   u.d = d;

   return (u.l==0x7FF8000000000000ll || u.l==0x7FF0000000000000ll || u.l==0xfff8000000000000ll);

}

int isinf(double d){

   union{
      unsigned long long l;
      double d;
   } u;
   u.d=d;

   return (u.l==0x7FF0000000000000ll?1:u.l==0xFFF0000000000000ll?-1:0);
}

double ceil(double x){
   double y = x;

    if( (*( ( (int *) &y)+1) & 0x80000000) != 0)//或者if(x<0)
		return (float)((int)x);
    else{

        if(x == 0)
        	return (float)((int)x);
        else
        	return (float)((int)x) + 1;
    }
}

double
floor(double x)
{
	double fract;

	if (x < 0.0) {
		x = -x;
		fract = modf(x, &x);
		if (fract != 0.0)
			x += 1;
		x = -x;
	} else
		modf(x, &x);
	return(x);
}

double frexp(double x, int *exptr){
	union{
		double d;
		unsigned char c[8];
	} u;
	u.d = x;
	//得到移码，并减去1022得到指数值。
	*exptr = (int)(((u.c[7] & 0x7f) << 4) | (u.c[6] >> 4)) - 1022;
	//把指数部分置为0x03FE
	u.c[7] &= 0x80;
	u.c[7] |= 0x3f;
	u.c[6] &= 0x0f;
	u.c[6] |= 0xe0;
	return u.d;
}

double ldexp(double v, int n){

   double two = 2.0;

   if (n < 0){
      n = -n; /*这句话和后面的if语句是用来对两位溢出码的机器*/
      if (n < 0) return 0.0;
      while (n > 0){
        if (n & 1) v /= two;
        two *= two;
         n >>= 1;

      }

   }

   else if (n > 0)

   {

      while (n > 0)

      {

        if (n & 1) v *= two;

        two *= two;

        n >>= 1;

      }

   }

   return v;

}

static double	log2	= 0.693147180559945309e0;
static double	ln10	= 2.302585092994045684;
static double	sqrto2	= 0.707106781186547524e0;
static double	p50	= -.240139179559210510e2;
static double	p51	= 0.309572928215376501e2;
static double	p52	= -.963769093377840513e1;
static double	p53	= 0.421087371217979714e0;
static double	q50	= -.120069589779605255e2;
static double	q51	= 0.194809660700889731e2;
static double	q52	= -.891110902798312337e1;

double log(double x){
	double arg = x;
	double xx,z, zsq, temp;
	int exp;

	if(arg <= 0.) {
		//errno = EDOM;
		return(-HUGE);
	}
	xx = frexp(arg,&exp);
	while(xx<0.5) {
		xx = xx*2;
		exp = exp-1;
	}
	if(xx<sqrto2) {
		xx = 2*xx;
		exp = exp-1;
	}

	z = (xx-1)/(xx+1);
	zsq = z*z;

	temp = ((p53*zsq + p52)*zsq + p51)*zsq + p50;
	temp = temp/(((1.0*zsq + q52)*zsq + q51)*zsq + q50);
	temp = temp*z + exp*log2;
	return(temp);
}

double log10(double x)
{
	return(log(x)/ln10);
}

double exp(double x){
	register double ret, value;

   __asm__(

      "fldl2e;"   

      "fmul %%st(1);"

      "fst  %%st(1);/n/t"

      "frndint;"        

      "fxch;/n/t"

      "fsub %%st(1);" 

      "f2xm1"

      : "=t" (ret), "=u" (value)

      : "0" (x)

   );

  

   ret += 1.0;

 

   __asm__(

      "fscale"

      : "=t" (ret)

      : "0" (ret), "u" (value)

   );

   return ret;
}

double tanh(double x){

	double ret,temp;

	if (x > 50)
		return 1;

	else if (x < -50)
		return -1;

	else{
		ret = exp(x);
		temp = 1.0 / ret;
		return ( (ret - temp) / (ret + temp));
	}

}//计算x的双曲正切值。

int abs(int x){
   return x < 0 ? -x : x;
}
long labs(long n){
   return (n >= 0 ? n : -n);
}
int fac(int n)
{
	register int i,f=1;
	for(i=1;i<=n;i++) f=f*i;
	return f;
}