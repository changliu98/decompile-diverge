int read_data(int fd, unsigned char *buf, unsigned int len) {
  int ret;
  unsigned int left;
  if (fd < 0) return -1;
  left = len;
  while (left > 0) {
    ret = read(fd, buf, left);
    if (ret <= 0) return -1;
    buf += ret;
    left -= ret;
  }
  return len;
}