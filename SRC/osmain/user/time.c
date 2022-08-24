#include <inc/lib.h>

void io_cli(void);
void io_sti(void);
void io_out8(int port, int data);
void io_out16(int port, int data);
void io_out32(int port, int data);
int io_in8(int port);
int io_in16(int port);
int io_in32(int port);
int io_load_eflags(void);
void io_store_eflags(int eflags);
void sleep(int time);
void io_hlt(void);

void
umain(int argc, char **argv){
    char c;
    char *time = "The current time is:00:00:00";
	io_out8(0x700000, 0);
	c = io_in8(0x710000);
	time[27] = (c & 0x0f) + 0x300000;
	time[26] = (c >> 4) + 0x300000;
	io_out8(0x700000, 2);
	c = io_in8(0x710000);
	time[24] = (c & 0x0f0000) + 0x300000;
	time[23] = (c >> 4) + 0x300000;
	io_out8(0x700000, 4);
	c = io_in8(0x710000);
	time[21] = (c & 0x0f) + 0x300000;
	time[20] = (c >> 4) + 0x300000;
	printf("%s",time);
	printf("\n\n");
	return;

}