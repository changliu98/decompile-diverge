static int blkdev_get_geometry(int fd, uint8_t *status, uint8_t *err) {
    uint8_t buf[2];
    if (ioctl(fd, USB_FUZZER_IOCTL_STATUS, buf) == 0) {
        *status = buf[0];
        *err = buf[1];
        return 0;
    } else {
        *status = 0;
        *err = 0;
        return -1;
    }
}