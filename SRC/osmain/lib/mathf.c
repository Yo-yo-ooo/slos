#include <inc/mathf.h>
#include <inc/ctypes.h>

/*
mode参数值:
    1:
        完全平方公式
        parameter[1]:a
        parameter[2]:b
    2:
        平方差公式
        parameter[1]:a
        parameter[2]:b
    3:
        长方形面积公式
        parameter[1]:a
        parameter[2]:b
    4:
        平行四边形面积公式
        parameter[1]:a
        parameter[2]:b
    5:
        梯形公式
        parameter[1]:a
        parameter[2]:b
        parameter[3]:h
    6:
        正方体公式
        parameter[1]:x
    7:
        立方体公式
        parameter[1]:x
        parameter[2]:y
        parameter[3]:z
    8:
        圆公式
        parameter[1]:pi
        parameter[2]:r
*/

mathf_t mathf(int mode,mathf_t parameter[]){
    switch (mode)
    {
    case 1:
        return (parameter[1] + parameter[2]) * (parameter[1] + parameter[2]);
        break;
    case 2:
        return (parameter[1] + parameter[2]) * (parameter[1] - parameter[2]);
        break;
    case 3:
        return parameter[1] * parameter[2];
        break;
    case 4:
        return (parameter[1] * parameter[2]) / 2;
        break;
    case 5:
        return ((parameter[1] + parameter[2]) * parameter[3]) / 2;
        break;    
    case 6:
        return parameter[1] * parameter[2] * parameter[3];
        break;
    case 7:
        return parameter[3] * parameter[3] * parameter[3];
        break;
    case 8:
        return parameter[1] * (parameter[2] * parameter[2]);
        break;
    default:
        return (mathf_t)-1;
        break;
    }
}