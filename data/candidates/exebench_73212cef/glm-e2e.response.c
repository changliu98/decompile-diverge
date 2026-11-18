int sendline(int fd, const void *buf, int n) {
    write(fd, buf, n);
    return n;
}