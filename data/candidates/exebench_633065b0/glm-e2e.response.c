int read_data(int fd, void *buf, unsigned int count) {
    if (fd < 0) {
        return -1;
    }

    unsigned int remaining = count;
    char *ptr = (char *)buf;

    while (remaining > 0) {
        int bytes_read = read(fd, ptr, remaining);
        if (bytes_read <= 0) {
            return -1;
        }
        ptr += bytes_read;
        remaining -= bytes_read;
    }

    return count - remaining;
}