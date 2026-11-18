int sendline(int fd, unsigned char *buf, int len) {
  write(fd, buf, len);
  return len;
}