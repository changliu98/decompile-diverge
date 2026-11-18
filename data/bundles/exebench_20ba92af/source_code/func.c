#include <sys/types.h>

#include <sys/stat.h>

#include <sys/ioctl.h>

#include <unistd.h>

#include <stdint.h>

#include <linux/hdreg.h>

#include <linux/fd.h>

int blkdev_get_start(int fd, unsigned int *s)
{

    struct hd_geometry geometry;

    if (ioctl(fd, 0x0301, &geometry) == 0) {
        *s = geometry.start;
        return 0;
    }


    (void) fd;
    *s = 0;
    return -1;
}
