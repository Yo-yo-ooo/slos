#ifndef JOS_INC_MALLOC_H
#define JOS_INC_MALLOC_H 1

#ifdef __cplusplus
extern "C" {
#endif

void *malloc(size_t size);
void free(void *addr);
char *sbrk(int n);
void *calloc(unsigned n, unsigned size);
void *realloc(void *ptr, size_t size);

#ifdef __cplusplus
}
#endif

#endif
