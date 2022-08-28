#include <inc/sys/window.h>
#include <inc/lib.h>
#include <inc/function.h>

void
umain(int argc, char **argv)
{
    winit();
    for(;;){
        io_hlt();
    }

}
