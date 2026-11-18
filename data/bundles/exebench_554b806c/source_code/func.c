#include <math.h>

#include <float.h>

#include <stdbool.h>

#include <stdlib.h>

#include <string.h>

#include <time.h>

#include <stdio.h>

static bool
is_empty(float *spectrum, int N)
{
  int k;
  for (k = 0; k <= N; k++)
  {
    if (spectrum[k] > FLT_MIN)
    {
      return false;
    }
  }
  return true;
}
