#ifndef _LIMITS_H
#define _LIMITS_H

#ifdef __cplusplus
extern "C" {
#endif

#define CHAR_BIT 8
#define SCHAR_MIN -128
#define SCHAR_MAX 127
#define UCHAR_MIN 0
#define UCHAR_MAX 255
#define CHAR_MIN SCHAR_MIN	/* type char sign-extends */
#define CHAR_MAX SCHAR_MAX	/* type char sign-extends */

#define SHRT_MIN -32768
#define SHRT_MAX 32767
#define USHRT_MIN 0
#define USHRT_MAX 65535

#define INT_MIN -2147483648
#define INT_MAX 2147483647
#define UINT_MIN 0
#define UINT_MAX 4294967295

#define LONG_MIN -2147483648
#define LONG_MAX 2147483647
#define ULONG_MIN 0
#define ULONG_MAX 4294967295
#define LLONG_MAX     9223372036854775807i64
#define LLONG_MIN   (-9223372036854775807i64 - 1)
#define ULLONG_MAX    0xffffffffffffffffui64

#define _I8_MIN     (-127i8 - 1)
#define _I8_MAX       127i8
#define _UI8_MAX      0xffui8

#define _I16_MIN    (-32767i16 - 1)
#define _I16_MAX      32767i16
#define _UI16_MAX     0xffffui16

#define _I32_MIN    (-2147483647i32 - 1)
#define _I32_MAX      2147483647i32
#define _UI32_MAX     0xffffffffui32

#define _I64_MIN    (-9223372036854775807i64 - 1)
#define _I64_MAX      9223372036854775807i64
#define _UI64_MAX     0xffffffffffffffffui64

#ifdef __cplusplus
}
#endif

#endif