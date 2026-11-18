void __cdecl dstsub4(int n, float *a)
{
  __m128i v2; // xmm1
  float xr; // [rsp+0h] [rbp-24h]

  if ( n >> 1 == 2 )
  {
    v2 = (__m128i)COERCE_UNSIGNED_INT(0.38268343 * 0.70710677);
    *(float *)v2.m128i_i32 = *(float *)v2.m128i_i32 * a[1];
    xr = (float)((float)(0.9238795 * 0.70710677) * a[3]) + COERCE_FLOAT(_mm_cvtsi128_si32(v2) ^ 0x80000000);
    a[3] = (float)((float)(0.38268343 * 0.70710677) * a[3]) + (float)((float)(0.9238795 * 0.70710677) * a[1]);
    a[1] = xr;
  }
  a[n >> 1] = 0.70710677 * a[n >> 1];
}