int readBytes(int handle, int addr, unsigned char *buf, int len)
{
 int ret;

 ret = ioctl(handle, 0x0703, addr);
 if (ret < 0)
  return -1;

 return read(handle, buf, len);
}