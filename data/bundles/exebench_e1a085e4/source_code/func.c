#include <stdio.h>

static inline void babl_matrix_to_float (const double *in, float *out)
{
  int i;
  for (i = 0; i < 9; i ++)
    out[i] = in[i];
}
