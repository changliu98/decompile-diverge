#include <sys/types.h>

#include <sys/stat.h>

#include <errno.h>

#include <unistd.h>

#include <libgen.h>

#include <stdlib.h>

int
read_all(int fd, unsigned char *buf, int count)
{
    int n;

    do {
        n = read(fd, buf, count);
        if (n > 0) {
            count -= n;
            buf += n;
        }
    } while (n > 0 && count > 0);

    return n;
}
