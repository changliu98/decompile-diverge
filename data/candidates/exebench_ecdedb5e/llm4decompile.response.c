int read_double(int fd, double *out)
{
  int err;
  double d;
  err = read(fd, &d, sizeof(double));
  *out = d;
  return err;
}