#include "chapter13.h"
#include <fcntl.h>
#include <malloc.h>
#include "../tlpi_hrd.h"

#define __USE_GNU

void direct_read(int argc,char** argv)
{
    int fd;
    ssize_t numRead;
    size_t length, alignment;
    off_t offset;
    char *buf;

    if (argc < 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s file length [offset [alignment]]\n", argv[0]);

    length = getLong(argv[2], GN_ANY_BASE, "length");
    offset = (argc > 3) ? getLong(argv[3], GN_ANY_BASE, "offset") : 0;
    alignment = (argc > 4) ? getLong(argv[4], GN_ANY_BASE, "alignment") : 4096;

    fd = open(argv[1], O_RDONLY | __O_DIRECT);
    
    if (fd == -1)
        errExit("open");

    /* memalign() allocates a block of memory aligned on an address that
       is a multiple of its first argument. By specifying this argument as
       2 * 'alignment' and then adding 'alignment' to the returned pointer,
       we ensure that 'buf' is aligned on a non-power-of-two multiple of
       'alignment'. We do this to ensure that if, for example, we ask
       for a 256-byte aligned buffer, we don't accidentally get
       a buffer that is also aligned on a 512-byte boundary. */

    buf = memalign(alignment * 2, length + alignment);
    if (buf == NULL)
        errExit("memalign");

    buf += alignment;

    if (lseek(fd, offset, SEEK_SET) == -1)
        errExit("lseek");

    numRead = read(fd, buf, length);
    if (numRead == -1)
        errExit("read");
    /*FIXME: should use %zd here, and remove (long) cast */
    printf("Read %ld bytes\n", (long) numRead);
}