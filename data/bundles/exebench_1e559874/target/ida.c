void __cdecl convolve_4(double *out, const double *left, const double *right)
{
  double r3; // [rsp+8h] [rbp-58h]
  double r2; // [rsp+10h] [rbp-50h]
  double r1; // [rsp+18h] [rbp-48h]
  double r0; // [rsp+20h] [rbp-40h]
  double l3; // [rsp+28h] [rbp-38h]
  double l2; // [rsp+30h] [rbp-30h]
  double l1; // [rsp+38h] [rbp-28h]
  double l0; // [rsp+40h] [rbp-20h]

  l0 = *left;
  r0 = *right;
  l1 = left[1];
  r1 = right[1];
  *out = *left * *right;
  l2 = left[2];
  r2 = right[2];
  out[1] = l0 * r1 + l1 * r0;
  l3 = left[3];
  r3 = right[3];
  out[2] = l2 * r0 + l0 * r2 + l1 * r1;
  out[3] = l3 * r0 + l2 * r1 + l0 * r3 + l1 * r2;
  out[4] = l3 * r1 + l1 * r3 + l2 * r2;
  out[5] = l2 * r3 + l3 * r2;
  out[6] = l3 * r3;
}