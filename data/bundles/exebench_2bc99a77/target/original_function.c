int blkdev_get_geometry(int fd, unsigned int *h, unsigned int *s)
{

    {
        struct hd_geometry geometry;

        if (ioctl(fd, 0x0301, &geometry) == 0) {
            *h = geometry.heads;
            *s = geometry.sectors;
            return 0;
        }
    }
# 184 "blkdev.c"
    (void) fd;
    *h = 0;
    *s = 0;
    return -1;
}