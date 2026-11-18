static ssize_t writen(int fd, unsigned char *ptr, size_t nbytes) {
 ssize_t nwritten;
 size_t nleft;

 nleft = nbytes;
 while (nleft > 0) {
  nwritten = write(fd, ptr, nleft);
  if (nwritten <= 0) return nwritten;
  nleft -= nwritten;
  ptr += nwritten;
 }
 return nbytes - nleft;
}