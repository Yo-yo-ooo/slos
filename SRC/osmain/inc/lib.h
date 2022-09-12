/* 
* Main public header file for our user-land support library,
* whose code lives in the lib directory.
* This library is roughly our OS's version of a standard C library,
* and is intended to be linked into all user-mode applications
* (NOT the kernel or boot loader).
*/

#ifndef JOS_INC_LIB_H
#define JOS_INC_LIB_H 1

#include <inc/types.h>
#include <inc/stdio.h>
#include <inc/stdarg.h>
#include <inc/string.h>
#include <inc/error.h>
#include <inc/assert.h>
#include <inc/env.h>
#include <inc/memlayout.h>
#include <inc/syscall.h>
#include <inc/trap.h>
#include <inc/fs.h>
#include <inc/fd.h>
#include <inc/args.h>
#include <inc/malloc.h>
#include <inc/ns.h>
#include <inc/time.h>
#include <inc/math.h>
#include <inc/limits.h>
#include <inc/float.h>
#include <inc/ctype.h>
#include <inc/stdint.h>
#include <inc/d_stdlib.h>

//FILE

#define OPEN_MAX	20
#define EOF			(-1)

#define _IOERR	040
#define	_IOEOF	020

typedef struct flag_field{
	unsigned is_read	: 1;
	unsigned is_write   : 1;
	unsigned is_unbuf   : 1;
	unsigned is_buf     : 1;
	unsigned is_eof     : 1;
	unsigned is_err     : 1;
}flag_field;

typedef struct _iobuf{
	int cnt;
	char *ptr;
	char *base;
	int flag;
	int fd;
}FILE;

enum _flags{
	_READ  = 01,
	_WRITE = 02,
	_UNBUF = 04,
	_EOF   = 010,
	_ERR   = 020
};

extern FILE __iob[OPEN_MAX];

#define stdin	(&__iob[0])
#define stdout	(&__iob[1])
#define stderr	(&__iob[2])

#define ferror(p)	(((p)->flag&_IOERR)!=0)
#define	feof(p)		(((p)->flag&_IOEOF)!=0)
#define fileno(p)	((p)->fd)

int _fillbuf(FILE *fp);
int _flushbuf(int x, FILE *fp);
int fflush(FILE *fp);
FILE *fopen(char *name, char *mode);
int  fclose(FILE *fp);

#define getc(p)		(--(p)->cnt >= 0 \
			? (unsigned char) *(p)->ptr++ : _fillbuf(p))

#define putc(x,p) 	(--(p)->cnt >= 0 \
				? *(p)->ptr++ = (x) : _flushbuf((x),p))

#define putchar(x)	putc((x), stdout)

struct arr {
	int num;
	struct arr* next;
};
typedef struct arr arr;


//END

//swap

#define swap(t,x,y)	{	t _z; \
						_z = y; \
						y = x; \
						x = _z;}

#define USED(x)		(void)(x)
#define OPEN_MAX 	20
#define BUFSIZ		1024


// main user program
void	umain(int argc, char **argv);

// libmain.c or entry.S
extern const char *binaryname;
extern const volatile struct Env *thisenv;
extern const volatile struct Env envs[NENV];
extern const volatile struct PageInfo pages[];

// exit.c
void	exit(void);

// pgfault.c
void	set_pgfault_handler(void (*handler)(struct UTrapframe *utf));

// readline.c
char*	readline(const char *buf);

// syscall.c
void	sys_cputs(const char *string, size_t len);
int	sys_cgetc(void);
envid_t	sys_getenvid(void);
int	sys_env_destroy(envid_t);
void	sys_yield(void);
static envid_t sys_exofork(void);
int	sys_env_set_status(envid_t env, int status);
int	sys_env_set_trapframe(envid_t env, struct Trapframe *tf);
int	sys_env_set_pgfault_upcall(envid_t env, void *upcall);
int	sys_page_alloc(envid_t env, void *pg, int perm);
int	sys_page_map(envid_t src_env, void *src_pg,
		     envid_t dst_env, void *dst_pg, int perm);
int	sys_page_unmap(envid_t env, void *pg);
int	sys_ipc_try_send(envid_t to_env, uint32_t value, void *pg, int perm);
int	sys_ipc_recv(void *rcv_pg);
unsigned int sys_time_msec(void);
int sys_pkt_send(void *addr, size_t len);
int sys_pkt_recv(void *addr, size_t *len);

// This must be inlined.  Exercise for reader: why?
static inline envid_t __attribute__((always_inline))
sys_exofork(void)
{
	envid_t ret;
	asm volatile("int %2"
		     : "=a" (ret)
		     : "a" (SYS_exofork), "i" (T_SYSCALL));
	return ret;
}

// ipc.c
void	ipc_send(envid_t to_env, uint32_t value, void *pg, int perm);
int32_t ipc_recv(envid_t *from_env_store, void *pg, int *perm_store);
envid_t	ipc_find_env(enum EnvType type);

// fork.c
#define	PTE_SHARE	0x400
envid_t	fork(void);
envid_t	sfork(void);	// Challenge!

// fd.c
int	close(int fd);
int creat(const char *file,int auth);
ssize_t	read(int fd, void *buf, size_t nbytes);
ssize_t	write(int fd, const void *buf, size_t nbytes);
int	seek(int fd, off_t offset);
void	close_all(void);
ssize_t	readn(int fd, void *buf, size_t nbytes);
int	dup(int oldfd, int newfd);
int	fstat(int fd, struct Stat *statbuf);
int	stat(const char *path, struct Stat *statbuf);

// file.c
int	open(const char *path, int mode);
int	ftruncate(int fd, off_t size);
int	remove(const char *path);
int	sync(void);


// pageref.c
int	pageref(void *addr);

// sockets.c
int     accept(int s, struct sockaddr *addr, socklen_t *addrlen);
int     bind(int s, struct sockaddr *name, socklen_t namelen);
int     shutdown(int s, int how);
int     connect(int s, const struct sockaddr *name, socklen_t namelen);
int     listen(int s, int backlog);
int     socket(int domain, int type, int protocol);

// nsipc.c
int     nsipc_accept(int s, struct sockaddr *addr, socklen_t *addrlen);
int     nsipc_bind(int s, struct sockaddr *name, socklen_t namelen);
int     nsipc_shutdown(int s, int how);
int     nsipc_close(int s);
int     nsipc_connect(int s, const struct sockaddr *name, socklen_t namelen);
int     nsipc_listen(int s, int backlog);
int     nsipc_recv(int s, void *mem, int len, unsigned int flags);
int     nsipc_send(int s, const void *buf, int size, unsigned int flags);
int     nsipc_socket(int domain, int type, int protocol);

// spawn.c
envid_t	spawn(const char *program, const char **argv);
envid_t	spawnl(const char *program, const char *arg0, ...);

// console.c
void	cputchar(int c);
int	iscons(int fd);
int	opencons(void);

// pipe.c
int	pipe(int pipefds[2]);
int	pipeisclosed(int pipefd);

// wait.c
void	wait(envid_t env);

//getenv.c
char *getenv(register char *name);

//system.c
void runcmd(char* s);
void system(char* s);

// dir

#define		S_IFMT	0170000		/* type of file */
#define		S_IFDIR	0040000	/* directory */
#define		S_IFCHR	0020000	/* character special */
#define		S_IFBLK	0060000	/* block special */
#define		S_IFREG	0100000	/* regular */
#define		S_IFLNK 0120000	/* symbolic link */
#define		S_ISUID	0004000		/* set user id on execution */
#define		S_ISGID	0002000		/* set group id on execution */
#define		S_IREAD	0000400		/* read permission, owner */
#define		S_IWRITE 0000200	/* write permission, owner */
#define		S_IEXEC	0000100		/* execute/search permission, owner */
#define		S_ICCTYP 0007000	/* type of concurrent access */
#define		S_ISYNC	0001000	/* 1 writer and n readers (synchronized access) */
#define		S_IEXCL	0003000	/* 1 writer or n readers (exclusive access) */
#define		S_IAPPEND	0005000	/* append only */
#define		S_IBLIND	0007000	/* blind directory */

/* File open modes */
#define	O_RDONLY	0x0000		/* open for reading only */
#define	O_WRONLY	0x0001		/* open for writing only */
#define	O_RDWR		0x0002		/* open for reading and writing */
#define	O_ACCMODE	0x0003		/* mask for above modes */

#define	O_CREAT		0x0100		/* create if nonexistent */
#define	O_TRUNC		0x0200		/* truncate to zero length */
#define	O_EXCL		0x0400		/* error if already exists */
#define O_MKDIR		0x0800		/* create directory, not regular file */

/*File creat modes*/

#define S_IRUSR		0x0000		/* open for reading only */
#define S_IWUSR 	0x0001      /* open for writing only */
#define S_IXUSR 	0x0002		
#define S_IRWXR 	0x0003

#endif	// !JOS_INC_LIB_H
