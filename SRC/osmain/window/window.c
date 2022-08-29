#include <inc/sys/window.h>
#include <inc/lib.h>
#include <inc/function.h>

void winit(void);

void
umain(int argc, char **argv)
{
    
    int i; /* 変数宣言。iという変数は、32ビットの整数型 */

	for (i = 0xa0000; i <= 0xaffff; i++) {
		write_mem8(i, i & 0x0f);
	}

	for (;;) {
		io_hlt();
	}

}
