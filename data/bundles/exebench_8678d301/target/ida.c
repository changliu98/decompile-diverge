float __cdecl vec_dot_prodf(const float *x, const float *y, int n)
{
  float z; // [rsp+0h] [rbp-1Ch]
  int i; // [rsp+4h] [rbp-18h]

  z = 0.0;
  for ( i = 0; i < n; ++i )
    z = (float)(x[i] * y[i]) + z;
  return z;
}