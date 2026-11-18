void __cdecl MultMat(const double *a, const double *b, double *c)
{
  int j; // [rsp+0h] [rbp-20h]
  int i; // [rsp+4h] [rbp-1Ch]

  for ( i = 0; i < 3; ++i )
  {
    for ( j = 0; j < 3; ++j )
      c[3 * i + j] = a[3 * i + 2] * b[j + 6] + a[3 * i] * b[j] + a[3 * i + 1] * b[j + 3];
  }
}