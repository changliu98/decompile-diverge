int I2CWrapperRead(int handle, int addr, char *buffer, int len)
{
 int rc;
 if (ioctl(handle, 0x0703, addr) < 0)
 {
  rc = -1;
 }
 else
 {
  rc = read(handle, buffer, len);
 }
 return rc;
}