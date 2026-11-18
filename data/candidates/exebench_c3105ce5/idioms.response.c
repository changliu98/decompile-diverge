static long writen(int fd, void *vptr, unsigned long n)
{
  unsigned long nleft;
  long nwritten;
  char *ptr;
  ptr = vptr;
  nleft = n;
  while (nleft > 0) {
    if ( (nwritten = write(fd, ptr, nleft)) <= 0)
      return nwritten;
    nleft -= nwritten;
    ptr += nwritten;
  }
  return n;
}