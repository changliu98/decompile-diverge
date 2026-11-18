int dupfd(int oldfd, int *newfd) {
  if (oldfd == -1) {
    *newfd = -1;
    return 1;
  }
  *newfd = dup(oldfd);
  return *newfd != -1;
}