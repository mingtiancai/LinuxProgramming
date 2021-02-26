#include "chapter20.h"
#include "../tlpi_hrd.h"
#include <signal.h>
#define _GNU_SOURCE
#include <string.h>


static void
sigHandler1(int sig)
{
    printf("Ouch!\n");                  /* UNSAFE (see Section 21.1.2) */
}

void ouch(int argc,char** argv)
{
    int j;

    /* Establish handler for SIGINT. Here we use the simpler signal()
       API to establish a signal handler, but for the reasons described in
       Section 22.7 of TLPI, sigaction() is the (strongly) preferred API
       for this task. */

    if (signal(SIGINT, sigHandler1) == SIG_ERR)
        errExit("signal");

    /* Loop continuously waiting for signals to be delivered */

    for (j = 0; j<20; j++) {
        printf("%d\n", j);
        sleep(3);                       /* Loop slowly... */
    }
}

static void
sigHandler2(int sig)
{
    static int count = 0;

    /* UNSAFE: This handler uses non-async-signal-safe functions
       (printf(), exit(); see Section 21.1.2) */

    if (sig == SIGINT) {
        count++;
        printf("Caught SIGINT (%d)\n", count);
        return;                 /* Resume execution at point of interruption */
    }

    /* Must be SIGQUIT - print a message and terminate the process */

    printf("Caught SIGQUIT - that's all folks!\n");
    exit(EXIT_SUCCESS);
}

void intquit(int argc,char** argv)
{
    /* Establish same handler for SIGINT and SIGQUIT. Here we use the
       simpler signal() API to establish a signal handler, but for the
       reasons described in Section 22.7 of TLPI, sigaction() is the
       (strongly) preferred API for this task. */

    if (signal(SIGINT, sigHandler2) == SIG_ERR)
        errExit("signal");
    if (signal(SIGQUIT, sigHandler2) == SIG_ERR)
        errExit("signal");

    for (;;)                    /* Loop forever, waiting for signals */
        pause();     
}

void t_kill(int argc,char** argv)
{
    int s, sig;

    printf("%d\n",getpid());
    if (signal(SIGINT, sigHandler2) == SIG_ERR)
        errExit("signal");

    if (argc != 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s pid sig-num\n", argv[0]);

    sig = getInt(argv[2], 0, "sig-num");

    s = kill(getLong(argv[1], 0, "pid"), sig);

    if (sig != 0) {
        if (s == -1)
            errExit("kill");

    } else {                    /* Null signal: process existence check */
        if (s == 0) {
            printf("Process exists and we can send it a signal\n");
        } else {
            if (errno == EPERM)
                printf("Process exists, but we don't have "
                       "permission to send it a signal\n");
            else if (errno == ESRCH)
                printf("Process does not exist\n");
            else
                errExit("kill");
        }
    }

}

/* NOTE: All of the following functions employ fprintf(), which
   is not async-signal-safe (see Section 21.1.2). As such, these
   functions are also not async-signal-safe (i.e., beware of
   indiscriminately calling them from signal handlers). */

static void                    /* Print list of signals within a signal set */
printSigset(FILE *of, const char *prefix, const sigset_t *sigset)
{
    int sig, cnt;

    cnt = 0;
    for (sig = 1; sig < NSIG; sig++) {
        if (sigismember(sigset, sig)) {
            cnt++;
            fprintf(of, "%s%d (%s)\n", prefix, sig, strsignal(sig));
        }
    }

    if (cnt == 0)
        fprintf(of, "%s<empty signal set>\n", prefix);
}

static int                     /* Print mask of blocked signals for this process */
printSigMask(FILE *of, const char *msg)
{
    sigset_t currMask;

    if (msg != NULL)
        fprintf(of, "%s", msg);

    if (sigprocmask(SIG_BLOCK, NULL, &currMask) == -1)
        return -1;

    printSigset(of, "\t\t", &currMask);

    return 0;
}

static int                     /* Print signals currently pending for this process */
printPendingSigs(FILE *of, const char *msg)
{
    sigset_t pendingSigs;

    if (msg != NULL)
        fprintf(of, "%s", msg);

    if (sigpending(&pendingSigs) == -1)
        return -1;

    printSigset(of, "\t\t", &pendingSigs);

    return 0;
}

