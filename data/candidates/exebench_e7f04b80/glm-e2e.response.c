int deo_pipe(int *read_fd, int *write_fd) {
    int pipefd[2];
    int ret;

    if (pipe(pipefd) != 0) {
        ret = errno;
    } else {
        *read_fd = pipefd[0];
        *write_fd = pipefd[1];
        ret = 0;
    }
    
    return ret;
}