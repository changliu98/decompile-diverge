int read_double(int fd, double *out)
{
  int ret = read(fd,&(*out),sizeof(*out));
  return ret;
}