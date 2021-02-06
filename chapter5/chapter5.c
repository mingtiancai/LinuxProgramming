#include "chapter5.h"

#include <sys/stat.h>
#include <fcntl.h>
#include "../tlpi_hrd.h"
#include <sys/uio.h>


void bad_exclusive_open(int argc,char** argv)
{
    int fd;

    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s file\n", argv[0]);

    fd = open(argv[1], O_WRONLY);       /* Open 1: check if file exists */
    if (fd != -1) 
    {                     /* Open succeeded */
        printf("[PID %ld] File \"%s\" already exists\n",
                (long) getpid(), argv[1]);
        close(fd);
    } 
    else 
    {
        if (errno != ENOENT)
        {          /* Failed for unexpected reason */
            errExit("open");
        } 
        else 
        {
            printf("[PID %ld] File \"%s\" doesn't exist yet\n",
                    (long) getpid(), argv[1]);
            if (argc > 2) 
            {             /* Delay between check and create */
                sleep(5);               /* Suspend execution for 5 seconds */
                printf("[PID %ld] Done sleeping\n", (long) getpid());
            }
            fd = open(argv[1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
            if (fd == -1)
                errExit("open");

            /*FIXME: should use %zd here, and remove (long) cast */
            printf("[PID %ld] Created file \"%s\" exclusively\n",
                    (long) getpid(), argv[1]);          /* MAY NOT BE TRUE! */
        }
    }

    exit(EXIT_SUCCESS);
}

void t_readv(int argc,char** argv)
{
    int fd;
    struct iovec iov[3];
    struct stat myStruct;       /* First buffer */
    int x;                      /* Second buffer */
#define STR_SIZE 100
    char str[STR_SIZE];         /* Third buffer */
    ssize_t numRead, totRequired;

    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s file\n", argv[0]);

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        errExit("open");

    totRequired = 0;

    iov[0].iov_base = &myStruct;
    iov[0].iov_len = sizeof(struct stat);
    totRequired += iov[0].iov_len;

    iov[1].iov_base = &x;
    iov[1].iov_len = sizeof(x);
    totRequired += iov[1].iov_len;

    iov[2].iov_base = str;
    iov[2].iov_len = STR_SIZE;
    totRequired += iov[2].iov_len;

    numRead = readv(fd, iov, 3);
    if (numRead == -1)
        errExit("readv");

    if (numRead < totRequired)
        printf("Read fewer bytes than requested\n");

    /*FIXME: should use %zd here, and remove (long) cast */
    printf("total bytes requested: %ld; bytes read: %ld\n",
            (long) totRequired, (long) numRead);
    exit(EXIT_SUCCESS);
}