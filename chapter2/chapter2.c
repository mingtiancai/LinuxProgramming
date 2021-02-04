#include <stdio.h>
#include "chapter2.h"
#include <gnu/libc-version.h>

void printGlibcVersion()
{

    printf("%d.%d\n",__GLIBC__,__GLIBC_MINOR__);
    char* versionPtr=gnu_get_libc_version();

    printf("%s\n",versionPtr);
}