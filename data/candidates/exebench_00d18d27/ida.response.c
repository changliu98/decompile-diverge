float __cdecl dotprod(float *B, float *C, int n)
{
  float sum; // [rsp+0h] [rbp-1Ch]
  int i; // [rsp+4h] [rbp-18h]

  sum = 0.0;
  for ( i = 0; i < n; ++i )
    sum = (float)(B[i] * C[i]) + sum;
  return sum;
}