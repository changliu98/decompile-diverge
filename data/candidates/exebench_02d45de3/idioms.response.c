int write_bus(int busfd, unsigned char *buf, int bufsize)
{
  return (write (busfd, buf, bufsize));
}