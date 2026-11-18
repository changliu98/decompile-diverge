int write_data(int fd, char *buf, int n) {
    int nread, left = n;
    char *ptr = buf;
    while (left > 0) {
        if ((nread = read(fd, ptr, left)) < 0) {
            return -1;
        } else if (nread == 0) {
            break; 
        }
        left -= nread;
        ptr += nread;
    }
    return n;
}