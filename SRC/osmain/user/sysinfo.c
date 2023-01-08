#include <inc/lib.h>

void
umain(int argc, char **argv)
{
	struct tm time;
    struct sysinfo info;
	sys_gettime(&time);
    bprintf(" __ _          _ _            __           _                 \n");
    bprintf("/ _\ | ___   _| (_)_ __   ___/ _\_   _ ___| |_ ___ _ __ ___  \n");
    bprintf("\ \| |/ / | | | | | '_ \ / _ \ \| | | / __| __/ _ \ '_ ` _ \ \n");
    bprintf("_\ \   <| |_| | | | | | |  __/\ \ |_| \__ \ ||  __/ | | | | |\n");
    bprintf("\__/_|\_\ __, |_|_|_| |_|\___\__/\__, |___/\__\___|_| |_| |_|\n");
    bprintf("         |___/                   |___/                       \n");
    bprintf("System Version: %s\n", "0.75c");
    bprintf("System Name: %s\n", SYS_NAME);
    bprintf("System time : [%t]\n",&time);
    sys_getinfo(&info);
    bprintf("CPU number  : %d CPUs online\n", info.ncpu);
    bprintf("Boot CPU    : %d CPU is boot CPU\n", info.bootcpu);
    bprintf("Memory size : Physical memory %uK\n", info.totalmem);
    PAUSE
}
