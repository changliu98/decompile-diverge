int write_bus(int fd, unsigned char *buf, int size) {
    return write(fd, buf, size);
}