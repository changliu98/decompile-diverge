int force_write(int fd, unsigned char *buf, int len) {
  int ret, total = 0;
  while (len > 0) {
    ret = write(fd, buf, len);
    if (ret <= 0) break;
    total += ret;
    buf += ret;
    len -= ret;
  }
  return total;
}