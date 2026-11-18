int read_all(int fd, void *buf, int count)
{
  int ret;
  do {
    ret = read(fd, buf, count);
    if (ret > 0) {
      count -= ret;
      buf = (char *)buf + ret;
    }
  } while (ret > 0 && count > 0);
  return ret;
}