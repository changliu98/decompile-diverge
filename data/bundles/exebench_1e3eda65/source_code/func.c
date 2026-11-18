#include <stdio.h>

#include <string.h>

#include <termios.h>

#include <sys/ioctl.h>

#include <unistd.h>

#include <fcntl.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <limits.h>

int Serial_WriteData(int portId, unsigned char *data, int length)
{
  return (write(portId, data, length));
}
