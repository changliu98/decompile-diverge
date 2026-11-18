int read_data(int fd, void *buf, int len)
{
  int ret;
  int left = len;
  if (fd < 0)
    return -1;
  while (left)
  {
    ret = read(fd, buf, left);
    if (ret <= 0)
      return -1;
    left -= ret;
    buf = (char *)buf + ret;
  }
  return len;
}