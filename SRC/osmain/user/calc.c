#include <inc/lib.h>

void
umain(int argc, char **argv){
    char operator;
    double firstNumber,secondNumber;

    printf("(+, -, *,): ");
    scanf("%c", &operator);
 
    printf("Input two number(format: a b): ");
    scanf("%lf %lf",&firstNumber, &secondNumber);
    
 
    switch(operator)
    {
        case '+':
            printf("%.1lf + %.1lf = %.1lf",firstNumber, secondNumber, firstNumber + secondNumber);
            break;
 
        case '-':
            printf("%.1lf - %.1lf = %.1lf",firstNumber, secondNumber, firstNumber - secondNumber);
            break;
 
        case '*':
            printf("%.1lf * %.1lf = %.1lf",firstNumber, secondNumber, firstNumber * secondNumber);
            break;
 
        case '/':
            printf("%.1lf / %.1lf = %.1lf",firstNumber, secondNumber, firstNumber / secondNumber);
            break;
 
        // operator doesn't match any case constant (+, -, *, /)
        default:
            printf("Error! operator is not correct");
    }

}