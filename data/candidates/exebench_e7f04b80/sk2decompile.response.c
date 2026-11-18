int deo_pipe(int *rfd, int *wfd) {
  int fds[2];
  int rc;
  rc = pipe(fds);
  if (rc) return errno;
  *rfd = fds[0];
  *wfd = fds[1];
  return 0;
}