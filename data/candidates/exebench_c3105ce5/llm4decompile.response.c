ssize_t writen(int fd, const void *buf, size_t count)
{
 size_t nleft = count;
 size_t nwritten;
 const char *bufp = buf;

 while (nleft > 0) {
  if ((nwritten = write(fd, bufp, nleft)) <= 0)
   return nwritten;

  nleft -= nwritten;
  bufp += nwritten;
 }

 return nwritten;
}