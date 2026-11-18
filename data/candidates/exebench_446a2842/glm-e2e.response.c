define CUSTOM_IOCTL 0x703

int readBytes(int fd, int offset, void *buf, int count) {
    int ret;

    // Call ioctl with the file descriptor, request 0x703, and the offset.
    // The third argument to ioctl is passed as an unsigned long (or void*),
    // but here it's taking the integer 'offset'.
    if (ioctl(fd, CUSTOM_IOCTL, (unsigned long)offset) < 0) {
        return -1;
    }

    // Read 'count' bytes into 'buf' from the file descriptor 'fd'
    ret = read(fd, buf, count);
    
    return ret;
}