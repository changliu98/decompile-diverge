int read_sock(int fd, void *buf, unsigned int size) {
    int bytes_read = -1;
    char *ptr = buf;
    unsigned int remaining = size;
    int retries = 0;

    while (remaining > 0) {
        bytes_read = read(fd, ptr, remaining);
        
        if (bytes_read > 0) {
            ptr += bytes_read;
            remaining -= bytes_read;
        }
        
        retries++;
        if (retries > 10000) {
            return -1;
        }
    }
    
    return remaining;
}