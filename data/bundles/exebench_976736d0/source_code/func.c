#include <time.h>

#include <unistd.h>

#include <errno.h>

static unsigned long div10quickm(unsigned long *tp)
{
 unsigned long q, r, t;
 t = *tp;
 q = (t >> 1) + (t >> 2);
 q = q + (q >> 4);
 q = q + (q >> 8);
 q = q + (q >> 16);
 q >>= 3;
 r = t - (((q << 2) + q) << 1);
 t = q + (r >> 9);
 *tp = t;
 t <<= 1;
 t = (t << 2) + t;
 return *tp - t;
}
