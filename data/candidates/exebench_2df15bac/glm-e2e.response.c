int force_write(int fd, void *buf, int count) {
    int total_written = 0;
    int bytes_written;

    while (count > 0) {
        bytes_written = write(fd, buf, (size_t)count);
        
        if (bytes_written <= 0) {
            break;
        }
        
        total_written += bytes_written;
        buf += bytes_written;
        count -= bytes_written;
    }
    
    return total_written;
}