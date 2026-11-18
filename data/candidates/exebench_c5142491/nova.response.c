int read_data(int fd, char *buf, int n) {
    int nread, left = n;
    char *ptr = buf;
    while (left > 0) {
        if ((nread = cread(fd, ptr, left)) < 0) {
            return -1;
        } else {
            left -= nread;
            ptr += nread;
        }
    }
    return n;
}