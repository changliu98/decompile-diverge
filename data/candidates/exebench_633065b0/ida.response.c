int __cdecl read_data(int fd, unsigned __int8 *buf, unsigned int buf_len)
{
  int size; // [rsp+Ch] [rbp-24h]
  unsigned int left_len; // [rsp+18h] [rbp-18h]

  if ( fd < 0 )
    return -1;
  for ( left_len = buf_len; left_len; left_len -= size )
  {
    size = read(fd, buf, left_len);
    if ( size <= 0 )
      return -1;
    buf += size;
  }
  return buf_len;
}