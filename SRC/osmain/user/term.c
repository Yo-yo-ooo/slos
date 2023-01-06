#include <inc/lib.h>

#define BACKGROUND 0x00
#define BUFSIZ 1024 /* Find the buffer overrun bug! */
int debug = 0;

int gettoken(char *s, char **token);
int builtin_cmd(char *cmdline);
void runcmd(char *s);
void usage(void);
int do_cd(char *cmdline);
void msh(int argc, char **argv);

struct interface interface;

void umain(int argc, char **argv)
{
    int i, r;
    int fd;
    int p[2];
    int readfd;
    int writefd;
    char *buf;
    char c;
    const volatile struct Env *e;
    interface_init(graph.scrnx, graph.scrny, graph.framebuffer, &interface);
    r = init_palette("/bin/term.plt", frame);
    if(r < 0)
        panic("term.plt cannot found!");
    r = draw_bitmap("/bin/termbg.bmp",0,0,&interface);
    if(r < 0)
        panic("term.png cannot found!");
    sys_updatescreen();
    close(1);
    if ((r = openscreen(&interface)) < 0)
        panic("fd = %e\n", r);
    cprintf("fd = %d\n", r);
    if ((r = pipe(p)) < 0)
    {
        cprintf("pipe: %e", r);
        exit();
    }
    readfd = p[0];
    writefd = p[1];
    r = fork();
    if (r == 0)
    {
        close(readfd);
        close(1);
        dup(writefd, 1);
        msh(argc, argv);
        printf("msh exit\n");
        exit();
    }
    else
    {
        close(writefd);
        close(0);
        if (readfd != 0)
            dup(readfd, 0);
        close(readfd);
    }

    e = &envs[ENVX(r)];
    while(1)
    {
        r = getchar();
        printf("%c", r);
        if(e->env_status == ENV_FREE)
            break;
    }
}

void msh(int argc, char **argv)
{
    int r, interactive, echocmds;
    struct Argstate args;
    struct tm time;
    char path[MAXPATH];
    char *buf;

    echocmds = 0;
    argstart(&argc, argv, &args);
    while ((r = argnext(&args)) >= 0)
        switch (r)
        {
        case 'd':
            debug++;
            break;
        case 'x':
            echocmds = 1;
            break;
        default:
            usage();
        }

    if (argc > 2)
        usage();
    if (argc == 2)
    {
        close(0);
        if ((r = open(argv[1], O_RDONLY)) < 0)
            panic("open %s: %e", argv[1], r);
        assert(r == 0);
    }

    // Spin for a bit to let the console quiet
    for (int i = 0; i < 15; ++i)
        sys_yield();

    while (1)
    {
        printf("\n");
        sys_gettime(&time);
        getcwd(path, MAXPATH);
        printf("# msh in %s ", path);
        printf("[%t]\n", &time);
        buf = readline("$ ");
        if (buf == NULL)
            exit();
        if (buf[0] == '#')
            continue;
        if (echocmds)
            printf("# %s\n", buf);
        if (builtin_cmd(buf))
            continue;
        if ((r = fork()) < 0)
            panic("fork: %e", r);
        if (debug)
            printf("FORK: %d\n", r);
        if (r == 0)
        {
            runcmd(buf);
            exit();
        }
        else
            wait(r);
    }
}

// Parse a shell command from string 's' and execute it.
// Do not return until the shell command is finished.
// runcmd() is called in a forked child,
// so it's OK to manipulate file descriptor state.
#define MAXARGS 16
void runcmd(char *s)
{
    char *argv[MAXARGS], *t, argv0buf[BUFSIZ];
    int argc, c, i, r, p[2], fd, pipe_child;
    char *name;

    pipe_child = 0;
    gettoken(s, 0);

again:
    argc = 0;
    while (1)
    {
        switch ((c = gettoken(0, &t)))
        {

        case 'w': // Add an argument
            if (argc == MAXARGS)
            {
                printf("too many arguments\n");
                exit();
            }
            argv[argc++] = t;
            break;

        case '<': // Input redirection
            // Grab the filename from the argument list
            if (gettoken(0, &t) != 'w')
            {
                printf("syntax error: < not followed by word\n");
                exit();
            }
            // Open 't' for reading as file descriptor 0
            // (which environments use as standard input).
            // We can't open a file onto a particular descriptor,
            // so open the file as 'fd',
            // then check whether 'fd' is 0.
            // If not, dup 'fd' onto file descriptor 0,
            // then close the original 'fd'.

            if (t[0] != '/')
                getcwd(argv0buf, MAXPATH);
            strcat(argv0buf, t);
            if ((fd = open(argv0buf, O_RDONLY)) < 0)
            {
                printf("Error open %s fail: %e", argv0buf, fd);
                exit();
            }
            if (fd != 0)
            {
                dup(fd, 0);
                close(fd);
            }
            break;

        case '>': // Output redirection
            // Grab the filename from the argument list
            if (gettoken(0, &t) != 'w')
            {
                printf("syntax error: > not followed by word\n");
                exit();
            }
            if (t[0] != '/')
                getcwd(argv0buf, MAXPATH);
            strcat(argv0buf, t);
            if ((fd = open(argv0buf, O_WRONLY | O_CREAT | O_TRUNC)) < 0)
            {
                printf("open %s for write: %e", argv0buf, fd);
                exit();
            }
            if (fd != 1)
            {
                dup(fd, 1);
                close(fd);
            }
            break;

        case '|': // Pipe
            if ((r = pipe(p)) < 0)
            {
                printf("pipe: %e", r);
                exit();
            }
            if (debug)
                printf("PIPE: %d %d\n", p[0], p[1]);
            if ((r = fork()) < 0)
            {
                printf("fork: %e", r);
                exit();
            }
            if (r == 0)
            {
                if (p[0] != 0)
                {
                    dup(p[0], 0);
                    close(p[0]);
                }
                close(p[1]);
                goto again;
            }
            else
            {
                pipe_child = r;
                if (p[1] != 1)
                {
                    dup(p[1], 1);
                    close(p[1]);
                }
                close(p[0]);
                goto runit;
            }
            panic("| not implemented");
            break;

        case 0: // String is complete
            // Run the current command!
            goto runit;

        default:
            panic("bad return %d from gettoken", c);
            break;
        }
    }

runit:
    // Return immediately if command line was empty.
    if (argc == 0)
    {
        if (debug)
            printf("EMPTY COMMAND\n");
        return;
    }

    name = argv[0];

    // Clean up command line.
    // Read all commands from the filesystem: add an initial '/' to
    // the command name.
    // This essentially acts like 'PATH=/'.
    if (argv[0][0] != '/')
    {
        getcwd(argv0buf, BUFSIZ);
        strcat(argv0buf, argv[0]);
        argv[0] = argv0buf;
    }
    argv[argc] = 0;

    // Print the command.
    if (debug)
    {
        printf("[%08x] SPAWN:", thisenv->env_id);
        for (i = 0; argv[i]; i++)
            printf(" %s", argv[i]);
        printf("\n");
    }

    // Spawn the command!
    if ((r = spawn(argv[0], (const char **)argv)) < 0)
    {
        snprintf(argv0buf, BUFSIZ, "/bin/%s", name);
        if ((r = spawn(argv0buf, (const char **)argv)) < 0)
            printf("spawn %s: %e\n", argv[0], r);
    }

    // In the parent, close all file descriptors and wait for the
    // spawned command to exit.
    close_all();
    if (r >= 0)
    {
        if (debug)
            printf("[%08x] WAIT %s %08x\n", thisenv->env_id, argv[0], r);
        wait(r);
        if (debug)
            printf("[%08x] wait finished\n", thisenv->env_id);
    }

    // If we were the left-hand part of a pipe,
    // wait for the right-hand part to finish.
    if (pipe_child)
    {
        if (debug)
            printf("[%08x] WAIT pipe_child %08x\n", thisenv->env_id, pipe_child);
        wait(pipe_child);
        if (debug)
            printf("[%08x] wait finished\n", thisenv->env_id);
    }

    // Done!
    exit();
}

// Get the next token from string s.
// Set *p1 to the beginning of the token and *p2 just past the token.
// Returns
//	0 for end-of-string;
//	< for <;
//	> for >;
//	| for |;
//	w for a word.
//
// Eventually (once we parse the space where the \0 will go),
// words get nul-terminated.
#define WHITESPACE " \t\r\n"
#define SYMBOLS "<|>&;()"

int _gettoken(char *s, char **p1, char **p2)
{
    int t;

    if (s == 0)
    {
        if (debug > 1)
            printf("GETTOKEN NULL\n");
        return 0;
    }

    if (debug > 1)
        printf("GETTOKEN: %s\n", s);

    *p1 = 0;
    *p2 = 0;

    while (strchr(WHITESPACE, *s))
        *s++ = 0;
    if (*s == 0)
    {
        if (debug > 1)
            printf("EOL\n");
        return 0;
    }
    if (strchr(SYMBOLS, *s))
    {
        t = *s;
        *p1 = s;
        *s++ = 0;
        *p2 = s;
        if (debug > 1)
            printf("TOK %c\n", t);
        return t;
    }
    *p1 = s;
    while (*s && !strchr(WHITESPACE SYMBOLS, *s))
        s++;
    *p2 = s;
    if (debug > 1)
    {
        t = **p2;
        **p2 = 0;
        printf("WORD: %s\n", *p1);
        **p2 = t;
    }
    return 'w';
}

// gettoken(s, 0) prepares gettoken for subsequent calls and returns 0.
// gettoken(0, token) parses a shell token from the previously set string,
// null-terminates that token, stores the token pointer in '*token',
// and returns a token ID (0, '<', '>', '|', or 'w').
// Subsequent calls to 'gettoken(0, token)' will return subsequent
// tokens from the string.
int gettoken(char *s, char **p1)
{
    static int c, nc;
    static char *np1, *np2;

    if (s)
    {
        nc = _gettoken(s, &np1, &np2);
        return 0;
    }
    c = nc;
    *p1 = np1;
    nc = _gettoken(np2, &np1, &np2);
    return c;
}

void usage(void)
{
    printf("usage: sh [-dix] [command-file]\n");
    exit();
}

int builtin_cmd(char *cmdline)
{
    int ret;
    int i;
    char cmd[20];
    for (i = 0; cmdline[i] != ' ' && cmdline[i] != '\0'; i++)
        cmd[i] = cmdline[i];
    cmd[i] = '\0';
    if (!strcmp(cmd, "quit") || !strcmp(cmd, "exit"))
        exit();
    if (!strcmp(cmd, "cd"))
    {
        ret = do_cd(cmdline);
        return 1;
    }
    if (!strcmp(cmd, "help"))
    {
        printf("Welcome to msh version 0.1!\n");
        printf("Type commands to execute them.\n");
        printf("Type 'exit' or 'quit' to exit.\n");
        printf("Have fun!\n");
        return 1;
    }
    return 0;
}

int do_cd(char *cmdline)
{
    char pathbuf[BUFSIZ];
    int r;
    pathbuf[0] = '\0';
    cmdline += 2;
    while (*cmdline == ' ')
        cmdline++;
    if (*cmdline == '\0')
        return 0;
    if (*cmdline != '/')
    {
        getcwd(pathbuf, BUFSIZ);
    }
    strcat(pathbuf, cmdline);
    if ((r = chdir(pathbuf)) < 0)
        printf("cd error : %e\n", r);
    return 0;
}