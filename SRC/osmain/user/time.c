#include <inc/lib.h>

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