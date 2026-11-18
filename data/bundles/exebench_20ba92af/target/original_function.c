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