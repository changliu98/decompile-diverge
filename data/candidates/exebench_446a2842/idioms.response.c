int readBytes(int busHandle, int addr, unsigned char *buf, int len)
{
  if ( ioctl(busHandle, 0x0703, addr) < 0 )
    return -1;
  return read(busHandle, buf, len);
}