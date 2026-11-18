int sendcw(int sock, unsigned char *cw) {
  if (send(sock, cw, 18, 0) == -1) {
    syslog(3, "ca.so: Send cw failed %d", errno);
    return 0;
  }
  return 1;
}