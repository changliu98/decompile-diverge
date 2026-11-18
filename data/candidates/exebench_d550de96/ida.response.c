int __cdecl sendbytes(int port, unsigned __int8 *data, int len)
{
  write(port, data, (unsigned int)len);
  return 0;
}