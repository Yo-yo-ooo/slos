#ifndef JOS_INC_MALLOC_H
#define JOS_INC_MALLOC_H 1

void *malloc(size_t size);
void free(void *addr);
char *sbrk(int n);
void *calloc(unsigned n, unsigned size);

#endif
