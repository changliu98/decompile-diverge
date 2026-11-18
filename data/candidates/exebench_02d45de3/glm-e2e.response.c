ssize_t write_bus(int fd, const void *buf, size_t count) {
    return write(fd, buf, count);
}