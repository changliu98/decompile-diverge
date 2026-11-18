int writen(int fd, unsigned char *buf, int n) {
  int nleft;
  int nwritten;
  nleft = n;
  while (nleft) {
    nwritten = write(fd, buf, nleft);
    if (nwritten <= 0) return nwritten;
    nleft -= nwritten;
    buf += nwritten;
  }
  return n;
}