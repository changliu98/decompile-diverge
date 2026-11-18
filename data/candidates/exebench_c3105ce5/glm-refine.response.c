ssize_t writen(int fd, const void *ptr, size_t nbytes)
{
  size_t nleft = nbytes;
  ssize_t nwritten;

  while (nleft > 0)
  {
    nwritten = write(fd, ptr, nleft);
    if (nwritten <= 0)
      return nwritten;
    
    nleft -= nwritten;
    ptr = (const char *)ptr + nwritten;
  }
  
  return nbytes;
}