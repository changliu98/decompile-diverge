void clean_fd(int fd, int *fds, int *count) {
    for (int i = 0; i < 2; i++) {
        if (fds[i] == fd) {
            fds[i] = 0;
        }
    }
    
    close(fd);
    (*count)--;
}