#ifndef __STDLIB__
#define __STDLIB__

#include <inc/types.h>

//macros

/*********2个字节为short型变量**********/
#define BYTE_TO_SHORT( byte ,byte1)       ( (byte<<8)  | byte1 )
/*********4个字节为int型变量**********/
#define BYTE_TO_INT( byte,byte1,byte2,byte3 )    ( (byte<<24) | (byte1 << 16) | (byte2 << 8) | byte3 )
/*********取i值的24-32位**********/
#define GET_1_BYTE(i)    (u_8)( ( (i) & 0xFF000000 ) >> 24 )
/*********取i值的16-24位**********/
#define GET_2_BYTE(i)    (u_8)( ( (i) & 0xFF0000 ) >> 16 ) 
/*********取i值的8-16位**********/
#define GET_3_BYTE(i)    (u_8)( ( (i) & 0xFF00 ) >> 8 )
/*********取i值的低8位**********/
#define GET_4_BYTE(i)    (u_8)( ( (i) & 0xFF ) >> 0 )
/*********判断x值的第i位是否为1**********/
#define X_CHKBIT( x , i )       ( ((x) >> (i) ) & 0x01 )
/**********把x值的第i位清为0**********/
#define X_CLRBIT( x , i )       ( (x) &= ( ~( 0x01 << (i) )))
/********把x值的第i位置为1*************/
#define X_SETBIT( x , i )       ( (x) |= ( 0x1 << (i) )) 
/*********short型变量为2个字节**********/
#define SHORT_TO_BYTE( Val ,byte)     do{ (byte)[0] = ((Val)>>8)&0xff;\
                                             (byte)[1] = (Val)&0xff;\
                                        }while(0)
/*********int型变量为4个字节**********/
#define INT_TO_BYTE( Val,byte )      do{ (byte)[0] = ((Val)>>24)&0xff;\
                                            (byte)[1] = ((Val)>>16)&0xff;\
                                            (byte)[2] = ((Val)>>8)&0xff;\
                                            (byte)[3] = ((Val))&0xff;\
                                        }while(0)

//structs 

typedef struct div{int quot;int rem;}div_t;
typedef struct ldiv{ long quot; long rem; }ldiv_t;

//functions
int atoi(char *str);
char *itoa(int value,char *string,int radix);
void ltoa(long num, char* str, int radix);
char *ultoa(unsigned long value, char *string, int radix);
double atof(const char *str);
long atol(const char *nptr);
u_8 Bin2BCD(u_8 BinCode);
u_8 Bcd2Bin(u_8 BcdCode);
div_t div(int num, int denom);
ldiv_t ldiv(long int num, long int denom);

#endif