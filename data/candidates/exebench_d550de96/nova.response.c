int sendbytes(int fd, char *buf, int n) {
    write(fd, buf, n);
    return 0;
}