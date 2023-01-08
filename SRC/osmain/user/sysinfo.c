#include <inc/lib.h>

void
umain(int argc, char **argv)
{
	struct tm time;
    struct sysinfo info;
	sys_gettime(&time);
    bprintf("____________________________________________\n");
    bprintf("/\\                                           \\\n");
    bprintf("\\_| He11o_Liu's MOS version 0.1              |\n");
    bprintf("  | A HOEEMADE MicroOS based on MIT6.828 JOS |\n");
    bprintf("  | Github: https://github.com/He11oLiu/MOS  |\n");
    bprintf("  | Blog  : http://blog.csdn.net/he11o_liu   |\n");
    bprintf("  | Blog  : http://www.cnblogs.com/he11o-liu |\n");
    bprintf("  |   _______________________________________|_\n");
    bprintf("   \\_/_________________________________________/\n");
    bprintf("\n");
    bprintf("System time : [%t]\n",&time);
    sys_getinfo(&info);
    bprintf("CPU number  : %d CPUs online\n", info.ncpu);
    bprintf("Boot CPU    : %d CPU is boot CPU\n", info.bootcpu);
    bprintf("Memory size : Physical memory %uK\n", info.totalmem);
}
