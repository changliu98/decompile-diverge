int read_data(int fd, char *buf, int count) {
    int n, left = count;
    char *ptr = buf;

    if (fd <= 0)
        return -1;

    while (left > 0) {
        if ((n = left) > BUFSIZ)
            n = BUFSIZ;
        if ((n = read(fd, ptr, n)) <= 0) {
            if (n == 0)
                break; 
            return -1;
        }
        left -= n;
        ptr += n;
    }
    return count - left;
}