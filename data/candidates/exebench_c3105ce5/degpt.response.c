ssize_t writen(int fd,uchar *ptr,size_t nbytes)

{
  size_t nleft;
  ssize_t nwritten;
  size_t nbytes_local;
  uchar *ptr_local;
  int fd_local;
  size_t local_10;
  
  nleft = nbytes;
  ptr_local = ptr;
  while ((local_10 = nbytes, nleft != 0 &&
         (local_10 = write(fd,ptr_local,nleft), 0 < (long)local_10))) {
    nleft = nleft - local_10;
    ptr_local = ptr_local + local_10;
  }
  return local_10;
}