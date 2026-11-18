int sendbytes(int fd, void *buf, unsigned int len) {
    write(fd, buf, len);
    return 0;
}