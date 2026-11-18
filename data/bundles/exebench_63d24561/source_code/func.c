#include <float.h>

#include <limits.h>

#include <math.h>

int
zmlt_(double* ar, double* ai, double* br, double* bi, double* cr, double* ci)
{
 double ca, cb;
# 3014 "zbsubs.c"
 ca = *ar * *br - *ai * *bi;
 cb = *ar * *bi + *ai * *br;
 *cr = ca;
 *ci = cb;
 return 0;
}
