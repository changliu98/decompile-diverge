int wfaCtrlRecv(int sock, unsigned char *buf) {
  int ret;
  ret = recv(sock, buf, 1024 - 1, 0);
  return ret;
}