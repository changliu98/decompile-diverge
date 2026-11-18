int cf_pipe(int fd[2]) {
  int ret;
  ret = pipe(fd);
  return ret;
}