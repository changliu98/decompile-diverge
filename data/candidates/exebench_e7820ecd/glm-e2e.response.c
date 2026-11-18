int read_all(int fd, void *buf, int count) {
    int bytes_read;
    int remaining = count;
    char *ptr = buf;

    do {
        bytes_read = read(fd, ptr, remaining);
        
        if (bytes_read > 0) {
            remaining -= bytes_read;
            ptr += bytes_read;
        }
    } while (bytes_read > 0 && remaining > 0);

    return bytes_read;
}