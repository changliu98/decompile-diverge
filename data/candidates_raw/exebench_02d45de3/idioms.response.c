int i2c_write(int busfd, unsigned char *buf, int bufsize)
{
  return (write (busfd, buf, bufsize));
}