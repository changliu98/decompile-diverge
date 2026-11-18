int readBytes(int fd, uint32_t speed, const char *driver,
                    int rxtx) {
    int ret;

    if (ioctl(fd, USB_RAW_IOCTL_SETRATE, speed) < 0) {
        ret = -1;
    } else {
        ret = func0_std(fd, driver, rxtx);
    }

    return ret;
}