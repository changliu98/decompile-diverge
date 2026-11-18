void __cdecl prod_vet(float *x, float *y, float *z)
{
  __m128i v3; // xmm1
  __m128i v4; // xmm1
  __m128i v5; // xmm1

  v3 = (__m128i)*(unsigned int *)z;
  *(float *)v3.m128i_i32 = *(float *)v3.m128i_i32 * y[1];
  x[2] = (float)(*y * z[1]) + COERCE_FLOAT(_mm_cvtsi128_si32(v3) ^ 0x80000000);
  v4 = (__m128i)*(unsigned int *)x;
  *(float *)v4.m128i_i32 = *(float *)v4.m128i_i32 * z[1];
  y[2] = (float)(*z * x[1]) + COERCE_FLOAT(_mm_cvtsi128_si32(v4) ^ 0x80000000);
  v5 = (__m128i)*(unsigned int *)y;
  *(float *)v5.m128i_i32 = *(float *)v5.m128i_i32 * x[1];
  z[2] = (float)(*x * y[1]) + COERCE_FLOAT(_mm_cvtsi128_si32(v5) ^ 0x80000000);
}