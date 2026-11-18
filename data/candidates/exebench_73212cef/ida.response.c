int __cdecl sendline(int port, unsigned __int8 *data, int len)
{
  write(port, data, (unsigned int)len);
  return len;
}