ssize_t writen(int fd, const void *buf, size_t n) {
    size_t nleft = n;
    ssize_t nwritten;
    ssize_t ret;

    while (nleft > 0) {
        nwritten = write(fd, buf, nleft);
        if (nwritten <= 0) {
            ret = nwritten;
            break;
        }
        nleft -= nwritten;
        buf += nwritten;
    }

    if (nleft == 0) {
        ret = n - nleft;
    }

    return ret;
}