int __cdecl read_sock(int sockhandle, unsigned __int8 *buf, int length)
{
  int i; // [rsp+8h] [rbp-28h]
  int byte_read; // [rsp+18h] [rbp-18h]

  i = 0;
  do
  {
    byte_read = read(sockhandle, buf, (unsigned int)length);
    if ( byte_read > 0 )
    {
      buf += byte_read;
      length -= byte_read;
    }
    if ( ++i > 10000 )
      return -1;
  }
  while ( length > 0 );
  return length;
}