double __cdecl icvDotProduct_32f(const float *src1, const float *src2, int len)
{
  double s = 0.0;
  for (int i = 0; i < len; ++i)
  {
    // The explicit (float) cast is kept to accurately represent the x87 FPU 
    // or SSE behavior where intermediate products are evaluated in single-precision 
    // before being accumulated into the double-precision sum.
    s += (double)(src1[i] * src2[i]);
  }
  return s;
}