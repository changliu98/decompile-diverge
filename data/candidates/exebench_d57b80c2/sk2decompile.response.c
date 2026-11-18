int i2c_multiple_writes(int fd, int length, unsigned char *data) {
  int ret;
  ret = write(fd, data, length);
  if (ret == -1 || ret != length) return -1;
  return ret;
}