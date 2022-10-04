#include <inc/stdio.h>
#include <inc/lib.h>

char *fgets(char *s, int n, FILE *iop){
    register int c;
    register char *cs;

    cs = s;
    while (--n > 0 && (c = getc(iop)) != EOF)
        if((*cs++ = c) == '\n')
            break;
    *cs = '\0';
    
    return (c == EOF && cs == s) ? NULL : s;
}

int fputs(char *s, FILE *iop){
    int c;

    while (c = *s++)
        putc(c, iop);
    return ferror(iop) ? EOF : 0;
}

fread(char *ptr, unsigned size, unsigned count, FILE *iop)
{
	register c;
	unsigned ndone, s;

	ndone = 0;
	if (size)
	for (; ndone<count; ndone++) {
		s = size;
		do {
			if ((c = getc(iop)) >= 0)
				*ptr++ = c;
			else
				return(ndone);
		} while (--s);
	}
	return(ndone);
}

fwrite(char *ptr, unsigned size, unsigned count, FILE *iop)
{
	register unsigned s;
	unsigned ndone;

	ndone = 0;
	if (size)
	for (; ndone<count; ndone++) {
		s = size;
		do {
			putc(*ptr++, iop);
		} while (--s);
		if (ferror(iop))
			break;
	}
	return(ndone);
}