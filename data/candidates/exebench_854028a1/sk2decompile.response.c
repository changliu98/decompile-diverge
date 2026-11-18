void closep(int *fd) {
  if (*fd >= 0) {
    close(*fd);
  }
  *fd = -1;
}