#include <inc/sys/window.h>
#include <inc/sys/io.h>
#include <inc/nasmfuc.h>

#define PIC1_DATA 0x21
#define PIC2_DATA 0xA1

void
umain(int argc, char **argv){
    outb(PIC1_DATA, 0b11111000);
    outb(PIC2_DATA, 0b11101111);

    asm("sti");

	for (;;) {
		asm ("hlt");
	}

}