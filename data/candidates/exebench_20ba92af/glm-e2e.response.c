For BLKGETSIZE

int blkdev_get_start(int fd, unsigned int *start) {
    unsigned long val;
    
    if (ioctl(fd, BLKGETSIZE, &val) == 0) {
        *start = (unsigned int)val;
        return 0;
    } else {
        *start = 0;
        return -1;
    }
}