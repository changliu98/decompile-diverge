int write_sock(int sockhandle, unsigned char *buf, int length)
{
  int ret = -1;
  ret = write(sockhandle, buf, length);
  return (length - ret);
}