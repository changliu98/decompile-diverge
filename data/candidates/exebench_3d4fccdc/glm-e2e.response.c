int write_sock(int fd, void *buf, int count) {
    int bytes_written = -1;
    
    bytes_written = write(fd, buf, count);
    
    return count - bytes_written;
}