#include "chapter18.h"

#include <sys/stat.h>
#include <fcntl.h>
#include "../tlpi_hrd.h"
#include <dirent.h>
#include <ftw.h>
#include <sys/stat.h>
#include <limits.h>
#include <libgen.h>

#define _XOPEN_SOURCE 600
#define CMD_SIZE 200
//#define BUF_SIZE 1024
#define BUF_SIZE PATH_MAX

void t_unlink(int argc,char** argv)
{
    int fd, j, numBlocks;
    char shellCmd[CMD_SIZE];            /* Command to be passed to system() */
    char buf[BUF_SIZE];                 /* Random bytes to write to file */

    if (argc < 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s temp-file [num-1kB-blocks] \n", argv[0]);

    numBlocks = (argc > 2) ? getInt(argv[2], GN_GT_0, "num-1kB-blocks")
                           : 100000;

    /* O_EXCL so that we ensure we create a new file */

    fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
    if (fd == -1)
        errExit("open");

    if (unlink(argv[1]) == -1)          /* Remove filename */
        errExit("unlink");

    for (j = 0; j < numBlocks; j++)     /* Write lots of junk to file */
        if (write(fd, buf, BUF_SIZE) != BUF_SIZE)
            fatal("partial/failed write");

    snprintf(shellCmd, CMD_SIZE, "df -k `dirname %s`", argv[1]);
    system(shellCmd);                   /* View space used in file system */

    if (close(fd) == -1)                /* File is now destroyed */
        errExit("close");
    printf("********** Closed file descriptor\n");

    /* See the erratum for page 348 at http://man7.org/tlpi/errata/.
       Depending on factors such as random scheduler decisions and the
       size of the file created, the 'df' command executed by the second
       system() call below does may not show a change in the amount
       of disk space consumed, because the blocks of the closed file
       have not yet been freed by the kernel. If this is the case,
       then inserting a sleep(1) call here should be sufficient to
       ensure that the the file blocks have been freed by the time
       of the second 'df' command.
    */

    system(shellCmd); 
}

// static void             /* List all files in directory 'dirpath' */
// listFiles(const char *dirpath)
// {
//     DIR *dirp;
//     struct dirent *dp;
//     Boolean isCurrent;          /* True if 'dirpath' is "." */

//     isCurrent = strcmp(dirpath, ".") == 0;

//     dirp = opendir(dirpath);
//     if (dirp  == NULL) {
//         errMsg("opendir failed on '%s'", dirpath);
//         return;
//     }argc,argventry in this directory, print directory + filename */

//     for (;;) {
//         errno = 0;              /* To distinguish error from end-of-directory */
//         dp = readdir(dirp);
//         if (dp == NULL)
//             break;

//         if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
//             continue;           /* Skip . and .. */

//         if (!isCurrent)
//             printf("%s/", dirpath);
//         printf("%s\n", dp->d_name);
//     }

//     if (errno != 0)
//         errExit("readdir");

//     if (closedir(dirp) == -1)
//         errMsg("closedir");
// }

// void list_files(int argc,char** argv)
// {
//     if (argc > 1 && strcmp(argv[1], "--help") == 0)
//         usageErr("%s [dir-path...]\n", argv[0]);

//     if (argc == 1)              /* No arguments - use current directory */
//         listFiles(".");
//     else
//         for (argv++; *argv; argv++)
//             listFiles(*argv);
// }

// static void
// usageError(const char *progName, const char *msg)
// {
//     if (msg != NULL)
//         fprintf(stderr, "%s\n", msg);
//     fprintf(stderr, "Usage: %s [-d] [-m] [-p] [directory-path]\n", progName);
//     fprintf(stderr, "\t-d Use FTW_DEPTH flag\n");
//     fprintf(stderr, "\t-m Use FTW_MOUNT flag\n");
//     fprintf(stderr, "\t-p Use FTW_PHYS flag\n");
//     exit(EXIT_FAILURE);
// }

// static int                      /* Function called by nftw() */
// dirTree(const char *pathname, const struct stat *sbuf, int type,
//         struct FTW *ftwb)
// {
//     if (type == FTW_NS) {                  /* Could not stat() file */
//         printf("?");
//     } else {
//         switch (sbuf->st_mode & S_IFMT) {  /* Print file type */
//         case S_IFREG:  printf("-"); break;
//         case S_IFDIR:  printf("d"); break;
//         case S_IFCHR:  printf("c"); break;
//         case S_IFBLK:  printf("b"); break;
//         case S_IFLNK:  printf("l"); break;
//         case S_IFIFO:  printf("p"); break;
//         case S_IFSOCK: printf("s"); break;
//         default:       printf("?"); break; /* Should never happen (on Linux) */
//         }
//     }

//     printf(" %s  ", (type == FTW_D)  ? "D  " : (type == FTW_DNR) ? "DNR" :
//             (type == FTW_DP) ? "DP " : (type == FTW_F)   ? "F  " :
//             (type == FTW_SL) ? "SL " : (type == FTW_SLN) ? "SLN" :
//             (type == FTW_NS) ? "NS " : "  ");

//     if (type != FTW_NS)
//         printf("%7ld ", (long) sbuf->st_ino);
//     else
//         printf("        ");

//     printf(" %*s", 4 * ftwb->level, "");        /* Indent suitably */
//     printf("%s\n",  &pathname[ftwb->base]);     /* Print basename */
//     return 0;                                   /* Tell nftw() to continue */
// }

// void nftw_dir_tree(int argc,char** argv)
// {
//      int flags, opt;

//     flags = 0;
//     while ((opt = getopt(argc, argv, "dmp")) != -1) {
//         switch (opt) {
//         case 'd': flags |= FTW_DEPTH;   break;
//         case 'm': flags |= FTW_MOUNT;   break;
//         case 'p': flags |= FTW_PHYS;    break;
//         default:  usageError(argv[0], NULL);
//         }
//     }

//     if (argc > optind + 1)
//         usageError(argv[0], NULL);

//     if (nftw((argc > optind) ? argv[optind] : ".", dirTree, 10, flags) == -1) {
//         perror("nftw");
//         exit(EXIT_FAILURE);
//     }
// }

void view_symlink(int argc,char** argv)
{
    struct stat statbuf;
    char buf[BUF_SIZE];
    ssize_t numBytes;

    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr("%s pathname\n", argv[0]);

    /* User lstat() to check whether the supplied pathname is
       a symbolic link. Alternatively, we could have checked to
       whether readlink() failed with EINVAL. */

    if (lstat(argv[1], &statbuf) == -1)
        errExit("lstat");

    if (!S_ISLNK(statbuf.st_mode))
        fatal("%s is not a symbolic link", argv[1]);

    numBytes = readlink(argv[1], buf, BUF_SIZE - 1);
    if (numBytes == -1)
        errExit("readlink");
    buf[numBytes] = '\0';                       /* Add terminating null byte */
    printf("readlink: %s --> %s\n", argv[1], buf);

    if (realpath(argv[1], buf) == NULL)
        errExit("realpath");
    printf("realpath: %s --> %s\n", argv[1], buf);
}

void t_dirbasename(int argc,char** argv)
{
    char *t1, *t2;
    int j;

    for (j = 1; j < argc; j++)  {
        t1 = strdup(argv[j]);
        if (t1 == NULL)
            errExit("strdup");
        t2 = strdup(argv[j]);
        if (t2 == NULL)
            errExit("strdup");

        printf("%s ==> %s + %s\n", argv[j], dirname(t1), basename(t2));

        free(t1);
        free(t2);
    }
}