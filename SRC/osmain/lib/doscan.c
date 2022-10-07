#include <inc/lib.h>
#include <lib/inline.h>

#define	FL_HASH		0x001	/* `#' seen */
#define FL_PLUS		0x002	/* `+' seen */
#define FL_RIGHT	0x004	/* `-' seen */
#define FL_BLANK	0x008	/* ` ' seen */
#define FL_SHORT	0x010	/* `h' seen */
#define FL_LONG		0x020	/* `l' seen */
#define FL_ZERO		0x040	/* `0' seen */
#define FL_DOT		0x080	/* '.' seen */
#define FL_UPPER	0x100	/* format character was uppercase */
#define FL_NUMBER	0x200	/* a number was formated %[douxefg] */


int _doscan(FILE * stream, const char *format, va_list ap){
	return 0;
}