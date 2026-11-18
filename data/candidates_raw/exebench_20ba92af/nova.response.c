int func0(int fd, int *status) {
    struct func0 fds;
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