int func0(int fd, char *buf, int n) {
    int nread, left = n;
    char *ptr = buf;

    while (left > 0) {
        if ((nread = cread(fd, ptr, left)) < 0) {
            if (nread == 0)
                break; 
            else
                return nread; 
        }
        left -= nread;
        ptr += nread;
    }

    return n - left; 
}