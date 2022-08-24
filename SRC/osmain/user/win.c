#include <inc/sys/window.h>
#include <inc/nasmfuc.h>

void
umain(int argc, char **argv){
    int i; /*i为DWORD４个字节*/
	char *p; /* p用于byte类型地址 */

	p = (char *) 0xa0000; /*  */

	for (i = 0; i <= 0xffff; i++) {
		*(p + i) = i & 0x0f;				//这样对内存进行赋值以后就会显示出图案了．
	}

	for (;;) {
		_io_hlt();
	}

}