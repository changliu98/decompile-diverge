int read_data(int fd, unsigned char *buf, int len) {
  int n, total;
  total = 0;
  while (total != len) {
    n = read(fd, buf + total, len - total);
    if (n <= 0) return -1;
    total += n;
  }
  return 0;
}