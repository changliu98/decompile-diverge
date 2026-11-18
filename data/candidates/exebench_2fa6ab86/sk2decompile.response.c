short recv_data(int sock, unsigned char *buf, unsigned short len) {
  short ret;
  ret = read(sock, buf, len);
  return ret;
}