#include <stdio.h>

#include <stdlib.h>

#include <limits.h>

#include <float.h>

static inline void mul_mat_vec_2(const float *m, const float *p, float *o)
{
  o[0] = p[0] * m[0] + p[1] * m[1];
  o[1] = p[0] * m[2] + p[1] * m[3];
}
