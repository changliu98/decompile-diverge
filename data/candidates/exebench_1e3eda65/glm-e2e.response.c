int Serial_WriteData(int fd, const void *buf, unsigned int count) {
    return write(fd, buf, (long)count);
}