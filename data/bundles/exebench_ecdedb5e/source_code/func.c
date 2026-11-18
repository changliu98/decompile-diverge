#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <fcntl.h>

#include <unistd.h>

#include <time.h>

#include <math.h>

#include <ctype.h>

#include <inttypes.h>

static int read_double(int fd,double *out)
{
 double d;
 int err;

 err=read(fd,&d,sizeof(d));
 *out=d;
do { } while(0);
 return err;
}
