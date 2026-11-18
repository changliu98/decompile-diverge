int readBytes(int fd, unsigned int addr, unsigned char *buf, int len) {
  int ret;
  ret = ioctl(fd, 0x0703, addr);
  if (ret < 0) return -1;
  return read(fd, buf, len);
}