int readBytes (int busHandle, int addr, unsigned char* buf, int len)
{
 if (ioctl (busHandle, I2C_SLAVE, addr) < 0)
  return -1;

 int n= read (busHandle, buf, len);

 return n;
}