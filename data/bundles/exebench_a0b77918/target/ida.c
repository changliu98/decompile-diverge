double __cdecl icvDotProduct_32f(const float *src1, const float *src2, int len)
{
  int i; // [rsp+0h] [rbp-24h]
  double s; // [rsp+4h] [rbp-20h]

  s = 0.0;
  for ( i = 0; i < len; ++i )
    s = (float)(src1[i] * src2[i]) + s;
  return s;
}