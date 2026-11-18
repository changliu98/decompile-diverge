void convolve_4(double *out, double *left, double *right)
{







  double l0, l1, l2, l3, r0, r1, r2, r3;

  l0 = left[0];
  l1 = left[1];
  l2 = left[2];
  l3 = left[3];
  r0 = right[0];
  r1 = right[1];
  r2 = right[2];
  r3 = right[3];
  out[0] = l0 * r0;
  out[1] = l0 * r1 + l1 * r0;
  out[2] = l0 * r2 + l1 * r1 + l2 * r0;
  out[3] = l0 * r3 + l1 * r2 + l2 * r1 + l3 * r0;
  out[4] = l1 * r3 + l2 * r2 + l3 * r1;
  out[5] = l2 * r3 + l3 * r2;
  out[6] = l3 * r3;

}