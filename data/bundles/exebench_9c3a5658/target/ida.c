void __cdecl cmatrix_from_frame(double *m, const double *v1, const double *v2, const double *v3)
{
  int i; // [rsp+0h] [rbp-24h]

  for ( i = 0; i < 3; ++i )
  {
    m[3 * i] = v1[i];
    m[3 * i + 1] = v2[i];
    m[3 * i + 2] = v3[i];
  }
}