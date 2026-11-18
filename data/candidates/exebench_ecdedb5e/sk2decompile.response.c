int read_double(int fd, double *d) {
  double dd;
  int n;
  n = read(fd, &dd, 8);
  *d = dd;
  return n;
}