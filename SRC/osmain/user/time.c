#include <inc/lib.h>
#include <inc/sys/io.h>

void
umain(int argc, char **argv){
    uint8_t c;
    char *time = "The current time is:00:00:00";
    outb(0x70,0);
    c = inb(0x71);
    time[27] = (c & 0x0f) + 0x30;
    time[26] = (c >> 4) + 0x30;
    outb(0x70, 2);
    c = inb(0x71);
    time[24] = (c & 0x0f) + 0x30;
    time[23] = (c >> 4) + 0x30;
    outb(0x70, 4);
    c = inb(0x71);
    time[21] = (c & 0x0f) + 0x30;
    time[20] = (c >> 4) + 0x30;
    printf("%s",time);
    printf("\n\n");
    return;
}