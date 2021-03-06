#include "chapter27.h"
#include "../tlpi_hrd.h"

extern char **environ;

void t_execve(int argc,char** argv)
{
    char *argVec[10];           /* Larger than required */
    char *envVec[] = { "GREET=salut", "BYE=adieu", NULL };

    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s pathname\n", argv[0]);

    /* Create an argument list for the new program */

    argVec[0] = strrchr(argv[1], '/');      /* Get basename from argv[1] */
    if (argVec[0] != NULL)
        argVec[0]++;
    else
        argVec[0] = argv[1];
    argVec[1] = "hello world";
    argVec[2] = "goodbye";
    argVec[3] = NULL;           /* List must be NULL-terminated */

    /* Execute the program specified in argv[1] */

    execve(argv[1], argVec, envVec);
    errExit("execve");          /* If we get here, something went wrong */
}

void envargs(int argc,char** argv)
{
    int j;
    char **ep;

    /* Display argument list */

    for (j = 0; j < argc; j++)
        printf("argv[%d] = %s\n", j, argv[j]);

    /* Display environment list */

    for (ep = environ; *ep != NULL; ep++)
        printf("environ: %s\n", *ep);

    exit(EXIT_SUCCESS);
}