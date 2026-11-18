int dupfd(int fd, int *out_fd) {
    int ret;
    
    if (fd == -1) {
        *out_fd = -1;
        ret = 1;
    } else {
        *out_fd = dup(fd);
        ret = (*out_fd != -1);
    }
    
    return ret;
}