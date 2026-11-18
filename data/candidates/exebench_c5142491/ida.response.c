int __cdecl read_data(int fd, unsigned __int8 *buf, int size)
{
  int ret; // [rsp+4h] [rbp-1Ch]
  int cur; // [rsp+8h] [rbp-18h]

  for ( cur = 0; cur != size; cur += ret )
  {
    ret = read(fd, &buf[cur], size - cur);
    if ( ret <= 0 )
      return -1;
  }
  return 0;
}