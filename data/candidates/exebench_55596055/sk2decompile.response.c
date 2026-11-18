void clean_fd(int fd, int *fds, int *fds_count) {
  int i;
  for (i = 0; i < 2; i++) {
    if (fds[i] == fd) {
      fds[i] = 0;
    }
  }
  close(fd);
  (*fds_count)--;
}