#include <inc/sys/window.h>
#include <inc/lib.h>
#include <inc/function.h>

void winit(void);

void
umain(int argc, char **argv)
{
    
    int i;
    char *p;
    
    p = (char *) 0xa0000;

    for(i = 0;i <= 0xffff;i++){
        *(p + i) = i & 0x0f;
    }

    for(;;){
        io_hlt();
    }

}
