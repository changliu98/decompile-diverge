int read_sock(int sock, unsigned char *buf, int len) {
  int count = 0;
  int ret;
  do {
    ret = read(sock, buf, len);
    if (ret > 0) {
      buf += ret;
      len -= ret;
    }
    count++;
    if (count > 10000) return -1;
  } while (len > 0);
  return len;
}