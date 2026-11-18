int __cdecl write_sock(int sockhandle, unsigned __int8 *buf, int length)
{
  return length - write(sockhandle, buf, (unsigned int)length);
}