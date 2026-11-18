int __cdecl shape_tria6(double *L, double *N)
{
  double L3; // [rsp+0h] [rbp-28h]
  double L2; // [rsp+8h] [rbp-20h]
  double L1; // [rsp+10h] [rbp-18h]

  L1 = *L;
  L2 = L[1];
  L3 = 1.0 - *L - L2;
  *N = *L * (*L + *L + -1.0);
  N[1] = 4.0 * L1 * L2;
  N[2] = L2 * (L2 + L2 + -1.0);
  N[3] = 4.0 * L2 * L3;
  N[4] = L3 * (L3 + L3 + -1.0);
  N[5] = 4.0 * L1 * L3;
  return 0;
}