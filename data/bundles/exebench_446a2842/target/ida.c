int __cdecl readBytes(int busHandle, int addr, unsigned __int8 *buf, int len)
{
  if ( ioctl(busHandle, 0x703uLL, (unsigned int)addr) >= 0 )
    return read(busHandle, buf, len);
  else
    return -1;
}