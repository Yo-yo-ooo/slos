#ifndef MATH_H
#define MATH_H

#include <inc/stdarg.h>
#include <inc/types.h>

float intpower(float a, int n);
int fact(int n);
double sin(double x);
double cos(double x);
double sqrt(double x);
double ABS(double x);
double Bernoulli(int x);//伯努利数
double log(double a);
double nth(double x,int n);
double absolute(double x);
double Factorial(int x);
double tan(double x);
double atan(double x, double y);
double asin(double x);
double acos(double x);

#define _E 2.71828182845904523536028747135266249775724709369995
#define pai 3.1415926535897932
#define ln2 0.693147

//math call numbers

enum mathcall {
    LN = 1/*ln function*/,EX/*e^x*/,
    YX/*y^x*/,SUM
};

typedef enum mathcall mathcall_t;

int64_t smathcall(mathcall_t callnumber, int64_t num,...);

#endif