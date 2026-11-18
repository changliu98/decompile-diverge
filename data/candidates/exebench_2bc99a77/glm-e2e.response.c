int blkdev_get_geometry(int fd, int *heads, int *sectors) {
    struct hd_geometry geo;
    int ret;

    if (ioctl(fd, 0x301, &geo) == 0) {
        *heads = geo.heads;
        *sectors = geo.sectors;
        ret = 0;
    } else {
        *heads = 0;
        *sectors = 0;
        ret = -1;
    }
    
    return ret;
}