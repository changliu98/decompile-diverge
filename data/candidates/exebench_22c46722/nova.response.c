int read_sock(int fd, char *buf, int n) {
    int nread, left = n;
    char *ptr = buf;
    while (left > 0) {
        if ((nread = read(fd, ptr, left)) == 0) {
            break;
        } else {
            left -= nread;
            ptr += nread;
        }
    }
    int ret = left;
    if (left > 0) {
        ret = -1;
    }
    return ret;
}