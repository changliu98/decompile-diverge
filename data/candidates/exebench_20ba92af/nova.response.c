int blkdev_get_start(int fd, int *status) {
    struct blkdev_get_start fds;
    int ret;

    ret = ioctl(fd, VISIOCTLSTATUS, &fds);
    if (ret == 0) {
        *status = fds.status;
        ret = 0;
    } else {
        *status = 0;
        ret = -1;
    }

    return ret;
}