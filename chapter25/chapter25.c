#include "chapter25.h"
#include <stdlib.h>
#include "../tlpi_hrd.h"

#define HAVE_ON_EXIT    

static void
atexitFunc1(void)
{
    printf("atexit function 1 called\n");
}

static void
atexitFunc2(void)
{
    printf("atexit function 2 called\n");
}

#ifdef HAVE_ON_EXIT
static void
onexitFunc(int exitStatus, void *arg)
{
    printf("on_exit function called: status=%d, arg=%ld\n",
                exitStatus, (long) arg);
}
#endif  

int exit_handlers(int argc,char** argv)
{
#ifdef HAVE_ON_EXIT
    if (on_exit(onexitFunc, (void *) 10) != 0)
        fatal("on_exit 1");
#endif
    if (atexit(atexitFunc1) != 0)
        fatal("atexit 1");
    if (atexit(atexitFunc2) != 0)
        fatal("atexit 2");
#ifdef HAVE_ON_EXIT
    if (on_exit(onexitFunc, (void *) 20) != 0)
        fatal("on_exit 2");
#endif

    exit(2);
}

void fork_stdio_buf(int argc,char** argv)
{
    printf("Hello world\n");
    write(STDOUT_FILENO, "Ciao\n", 5);

    //fflush(stdout);

        

    switch (fork())
    {
    case -1:
        errExit("fork");
    case 0:
        printf("child\n");
        exit(EXIT_SUCCESS);
    
    default:
        printf("parent\n");
        exit(EXIT_SUCCESS);
    }
}