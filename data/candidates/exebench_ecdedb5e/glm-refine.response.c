ssize_t read_double(int fd, double *out)
{
  double d;
  ssize_t err;

  err = read(fd, &d, sizeof(double));
  *out = d;
  return err;
}