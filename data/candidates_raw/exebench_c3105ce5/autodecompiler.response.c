ssize_t write_line(int sock, char *buffer, size_t len) {
    size_t nleft = len;
    ssize_t nwritten;
    while (1) {
        if (nleft > 0) {
            nwritten = write(sock, buffer, nleft);
            if (nwritten <= 0) {
                return nwritten;
            }
            else {
                nleft -= nwritten;
                buffer += nwritten;
            }
        }
        else {
            return len - nleft;
        }
    }
}