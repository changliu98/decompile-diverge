int __cdecl write_buff(int fd, unsigned __int8 *data, ssize_t size)
{
  signed __int64 sz; // [rsp+0h] [rbp-30h]
  __int64 n; // [rsp+8h] [rbp-28h]
  int sizea; // [rsp+18h] [rbp-18h]

  sizea = size;
  sz = size;
  while ( sz > 0 )
  {
    n = write(fd, data, sz);
    if ( n < 0 )
      return -1;
    sz -= n;
    data += n;
  }
  return sizea;
}