int sendbytes(int sock, unsigned char *buf, int len) {
  int n;
  n = write(sock, buf, len);
  return 0;
}