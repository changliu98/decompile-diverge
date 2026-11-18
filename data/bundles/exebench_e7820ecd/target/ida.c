int __cdecl read_all(int fd, unsigned __int8 *buf, int count)
{
  bool v4; // [rsp+7h] [rbp-19h]
  int n; // [rsp+8h] [rbp-18h]

  do
  {
    n = read(fd, buf, count);
    if ( n > 0 )
    {
      count -= n;
      buf += n;
    }
    v4 = 0;
    if ( n > 0 )
      v4 = count > 0;
  }
  while ( v4 );
  return n;
}