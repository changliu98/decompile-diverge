#include <unistd.h>

#include <sys/ioctl.h>

#include <linux/i2c-dev.h>

#include <time.h>

#include <fcntl.h>

int I2CSensor_Read(int *bus,unsigned char I2CAddress,unsigned char registry,unsigned char *buffer,int size)
{

 if (ioctl(*bus,I2C_SLAVE,I2CAddress)<0)
  return 3;


 if (write(*bus,&registry,1)!=1)
  return 3;


 if (read(*bus,buffer,size)!=size)
  return 3;

 return 0;
}
