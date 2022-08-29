#ifndef _MATH_H
#define _MATH_H

#define MAXFLOAT	((float)3.40282346638528860e+38)
#define HUGE	MAXFLOAT

double sqrt(double x);
double atan(double x);
double atan2(double x,double y);
double pow(double x, double y);
double fabs(double x);
double sin(double x);
double cos(double x);
double tan(double x);
double asin(double x);
double acos(double x);
double modf(double x, double *ip);
double ceil(double x);
double frexp(double x, int *exptr);
double ldexp(double v, int n);
double log(double x);
double log10(double x);
double exp(double x);
double tanh(double x);
int    abs(int x);
long labs(long n);
int fac(int n);
double Factorial(int x);
double Bernoulli(int x);
float intpower(float a, int n);
float ln(float x);
int fact(int n);

#endif