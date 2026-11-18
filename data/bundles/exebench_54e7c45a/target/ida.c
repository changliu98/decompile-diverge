int __cdecl matMultMV(double *m, double *v, double *r2)
{
  double r_8; // [rsp+8h] [rbp-38h]
  double r_16; // [rsp+10h] [rbp-30h]
  double r_24; // [rsp+18h] [rbp-28h]

  r_8 = m[7] * v[3] + m[6] * v[2] + m[4] * *v + m[5] * v[1];
  r_16 = m[11] * v[3] + m[10] * v[2] + m[8] * *v + m[9] * v[1];
  r_24 = m[15] * v[3] + m[14] * v[2] + m[12] * *v + m[13] * v[1];
  *r2 = m[3] * v[3] + m[2] * v[2] + *m * *v + m[1] * v[1];
  r2[1] = r_8;
  r2[2] = r_16;
  r2[3] = r_24;
  return 0;
}