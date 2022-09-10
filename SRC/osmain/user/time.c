#include <inc/lib.h>

void
umain(int argc, char **argv){
    time_t tim = NULL;
	struct tm *t = NULL;
	long timb;
	
	char time = asctime(l_gmtime(&timb));
	printf("%s",time);
	
	printf("\n\n");
	return;
}