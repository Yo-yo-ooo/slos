#include <inc/sys/window.h>
#include <inc/sys/io.h>

void io_hlt(void);

void
umain(int argc, char **argv){
	//进入0x10显示
	clear();

/*
	int i; //i为DWORD４个字节
	char *p; //p用于byte类型地址 

	p = (char *) 0xa0000; 

	for (i = 0; i <= 0xffff; i++) {
		*(p + i) = i & 0x0f;				//这样对内存进行赋值以后就会显示出图案了．
	}

	for (;;) {
		io_hlt();
	} 
	*/

}