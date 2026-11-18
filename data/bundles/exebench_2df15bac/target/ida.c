int __cdecl force_write(int fd, unsigned __int8 *buf, int sz)
{
  int rd; // [rsp+4h] [rbp-1Ch]
  int got; // [rsp+8h] [rbp-18h]

  got = 0;
  while ( sz > 0 )
  {
    rd = write(fd, buf, sz);
    if ( rd <= 0 )
      break;
    got += rd;
    buf += rd;
    sz -= rd;
  }
  return got;
}