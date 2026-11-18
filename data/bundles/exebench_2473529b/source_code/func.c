#include <stdio.h>

#include <stdlib.h>

#include <stdint.h>

#include <math.h>

#include <sys/time.h>

#include <errno.h>

#include <time.h>

void normalize_angle(double *angle)
{

 while (*angle > (360.0 * (3.14159265) / 180.0))
  *angle -= (360.0 * (3.14159265) / 180.0);
 while (*angle < 0)
  *angle += (360.0 * (3.14159265) / 180.0);
}
