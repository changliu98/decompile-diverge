int write_sock(int sock, unsigned char *buf, int len) {
  int ret;
  ret = write(sock, buf, len);
  if (ret < 0) {
    return ret;
  }
  return len - ret;
}