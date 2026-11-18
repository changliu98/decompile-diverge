int write_bus(int fd, unsigned char *buf, int len) {
  int ret;
  ret = write(fd, buf, len);
  return ret;
}