void __cdecl flt_cvt(float *xptr, double x)
{
  float v2; // xmm0_4

  v2 = x;
  *xptr = v2;
}