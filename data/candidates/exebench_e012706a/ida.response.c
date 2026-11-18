void __cdecl cmatrix_to_frame(const double *m, double *v1, double *v2, double *v3)
{
  int i; // [rsp+0h] [rbp-24h]

  for ( i = 0; i < 3; ++i )
  {
    v1[i] = m[3 * i];
    v2[i] = m[3 * i + 1];
    v3[i] = m[3 * i + 2];
  }
}