#include <math.h>

static void
vscale(float dst[3], float src[3], float scale)
{
  dst[0] = src[0] * scale;
  dst[1] = src[1] * scale;
  dst[2] = src[2] * scale;
}
