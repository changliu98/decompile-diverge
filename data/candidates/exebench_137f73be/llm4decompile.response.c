int I2CSensor_Read(int *fd, int address, int reg, unsigned char *data, int size)
{
 int ret;


 ret = ioctl(*fd, 0x0703, address);
 if(ret < 0)
  return 3;


 if(write(*fd, &reg, 1) != 1)
  return 3;


 if(read(*fd, data, size) != size)
  return 3;

 return 0;
}