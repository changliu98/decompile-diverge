int force_write(int fd, void *buf, int len)
{
  int ret = 0;
  int n = len;
  while (n > 0) {
    ret = write(fd, buf, n);
    if (ret <= 0)
      break;
    ret += ret;
    buf = (char *)buf + ret;
    n -= ret;
  }
  return ret;
}