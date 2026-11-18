#include <errno.h>

#include <string.h>

#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <linux/i2c-dev.h>

#include <sys/ioctl.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <fcntl.h>

#include <getopt.h>

static int write_bus(int busfd, unsigned char *buf, int bufsize)
{
 return write(busfd, buf, bufsize);
}
