void __cdecl Sqrt(float x, float *res)
{
  __m128i v2; // xmm1
  int i; // [rsp+0h] [rbp-18h]
  float xa; // [rsp+14h] [rbp-4h]

  i = 1597463007 - (SLODWORD(x) >> 1);
  v2 = (__m128i)COERCE_UNSIGNED_INT(0.5 * x);
  *(float *)v2.m128i_i32 = (float)(0.5 * x) * *(float *)&i;
  xa = *(float *)&i * (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32(v2) ^ 0x80000000) * *(float *)&i) + 1.5);
  if ( xa <= 0.0 )
    *res = 0.0;
  else
    *res = 1.0 / xa;
}