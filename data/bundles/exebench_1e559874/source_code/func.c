#include <stdlib.h>

static void
convolve_4 (double *out, const double *left, const double *right)


{
  double l0, l1, l2, l3, r0, r1, r2, r3;
  double a;

  l0 = left[0];
  r0 = right[0];
  a = l0 * r0;
  l1 = left[1];
  r1 = right[1];
  out[0] = a;
  a = (l0 * r1) + (l1 * r0);
  l2 = left[2];
  r2 = right[2];
  out[1] = a;
  a = (l0 * r2) + (l1 * r1) + (l2 * r0);
  l3 = left[3];
  r3 = right[3];
  out[2] = a;

  out[3] = (l0 * r3) + (l1 * r2) + (l2 * r1) + (l3 * r0);
  out[4] = (l1 * r3) + (l2 * r2) + (l3 * r1);
  out[5] = (l2 * r3) + (l3 * r2);
  out[6] = l3 * r3;
}
