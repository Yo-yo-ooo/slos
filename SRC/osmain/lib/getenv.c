#include <inc/lib.h>

static char *nvmatch(register char *s1, register char *s2)
{

	while (*s1 == *s2++)
		if (*s1++ == '=')
			return(s2);
	if (*s1 == '\0' && *(s2-1) == '=')
		return(s2);
	return(NULL);
}

char *getenv(register char *name){
    char **environ;
	register char **p = environ;
	register char *v;

	while (*p != NULL)
		if ((v = nvmatch(name, *p++)) != NULL)
			return(v);
	return(NULL);
}