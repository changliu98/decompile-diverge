long __cdecl metric(double *x, double *y, double *z, double *M)
{
  int i; // [rsp+0h] [rbp-24h]

  for ( i = 0; i < 9; ++i )
    M[i] = 0.0;
  M[8] = 1.0;
  M[4] = 1.0;
  *M = 1.0;
  return 0LL;
}