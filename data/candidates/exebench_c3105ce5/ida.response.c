ssize_t __cdecl writen(int fd, unsigned __int8 *ptr, size_t nbytes)
{
  size_t nleft; // [rsp+0h] [rbp-30h]
  __int64 nwritten; // [rsp+8h] [rbp-28h]

  nleft = nbytes;
  while ( nleft )
  {
    nwritten = write(fd, ptr, nleft);
    if ( nwritten <= 0 )
      return nwritten;
    nleft -= nwritten;
    ptr += nwritten;
  }
  return nbytes;
}