int I2CSensor_Read(I2CWrapper *i2c, unsigned char address, unsigned char reg, unsigned char* buffer, int len)
{
 int ret = 0;
 if (ioctl(i2c->fd, 0x0703, address) < 0)
 {
  ret = 3;
 }
 else
 {
  if (write(i2c->fd, &reg, 1) != 1)
  {
   ret = 3;
  }
  else
  {
   if (read(i2c->fd, buffer, len) != len)
   {
    ret = 3;
   }
   else
   {
    ret = 0;
   }
  }
 }
 return ret;
}