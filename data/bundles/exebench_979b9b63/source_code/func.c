#include <unistd.h>

#include <sys/ioctl.h>

#include <linux/i2c-dev.h>

#include <time.h>

#include <fcntl.h>

int openI2CBus(int *bus,char * device)
{
        *bus = open(device, O_RDWR);
        if (*bus<0)
         return 1;

        return 0;
}
