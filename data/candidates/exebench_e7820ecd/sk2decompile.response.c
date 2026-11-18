int read_all(int fd, unsigned char *buf, int len) {
  int r;
  do {
    r = read(fd, buf, len);
    if (r > 0) {
      len -= r;
      buf += r;
    }
  } while (r > 0 && len > 0);
  return r;
}