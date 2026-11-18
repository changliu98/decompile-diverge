int func0(int fd, int size, char *buf) {
    int nread = 0;
    int nleft = size;
    if ((nread = read(fd, buf, nleft)) == -1) {
        return -1;
    } else {
        nleft -= nread;
    }
    return nleft;
}