int write_buff(int fd, void *buf, long count)
{
  while (count > 0) {
    long ret = write(fd, buf, count);
    if (ret < 0)
      return -1;
    count -= ret;
    buf += ret;
  }
  return (int)count;
}