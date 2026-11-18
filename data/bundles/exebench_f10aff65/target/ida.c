float __cdecl dot(float *a, float *b, int n)
{
  int i; // [rsp+0h] [rbp-1Ch]
  float sum; // [rsp+4h] [rbp-18h]

  sum = 0.0;
  for ( i = 0; i < n; ++i )
    sum = (float)(a[i] * b[i]) + sum;
  return sum;
}