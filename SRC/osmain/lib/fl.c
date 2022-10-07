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

int fgetc(FILE *fp)
{
	return(getc(fp));
}

int fputs(char *s, FILE *iop){
    int c;

    while (c = *s++)
        putc(c, iop);
    return ferror(iop) ? EOF : 0;
}

int fputc(int c, FILE *fp){
    return(putc(c,fp));
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


FILE *freopen(char *file, char *mode, FILE *iop){
	char ffile;
	extern int errno;
	register f, rw;

	rw = mode[1] == '+';

	if (*mode=='w') {
		f = creat(file, 0666);
		if (rw && f>=0) {
			close(f);
			f = open(file, 2);
		}
	} else if (*mode=='a') {
		if ((f = open(file, rw? 2: 1)) < 0) {
			if (errno == ENOENT) {
				f = creat(file, 0666);
				if (rw && f>=0) {
					close(f);
					f = open(file, 2);
				}
			}
		}
		if (f >= 0)
			lseek(f, 0L, 2);
	} else
		f = open(file, rw? 2: 0);
	fclose(iop);
	if (f < 0)
		return(NULL);
	iop->cnt = 0;
	ffile = f;
	if (rw)
		iop->flag |= _IORW;
	else if (*mode != 'r')
		iop->flag |= _IOWRT;
	else
		iop->flag |= _IOREAD;
	return(iop);
}

int ungetc(int c, FILE *iop){
	if (c == EOF)
		return(-1);
	if ((iop->flag&_IOREAD)==0 || iop->ptr <= iop->base)
		if (iop->ptr == iop->base && iop->cnt==0)
			iop->ptr++;
		else
			return(-1);
	iop->cnt++;
	*--iop->ptr = c;
	return(0);
}