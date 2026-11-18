int __cdecl write_bus(int busfd, unsigned __int8 *buf, int bufsize)
{
  return write(busfd, buf, bufsize);
}