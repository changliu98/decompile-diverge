int write_buff(int fd, void *buf, unsigned long count) {
    char *current_buf = buf;
    long remaining = count;
    int ret;

    while (remaining > 0) {
        long bytes_written = write(fd, current_buf, remaining);
        
        if (bytes_written < 0) {
            return -1;
        }
        
        remaining -= bytes_written;
        current_buf += bytes_written;
    }
    
    return (int)count;
}