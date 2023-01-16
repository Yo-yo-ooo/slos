#ifndef _STDDEF_
#define _STDDEF

#include <inc/cppinc/crtdef.h>
#include <types.h>

C_HEAHER

typedef int ptrdiff_t;
typedef int intptr_t;

#ifdef __cplusplus
    #define offsetof(s,m) ((::size_t)&reinterpret_cast<char const volatile&>((((s*)0)->m)))
#else
    #define offsetof(s,m) ((size_t)&(((s*)0)->m))
#endif

C_HEAHER_END

#endif