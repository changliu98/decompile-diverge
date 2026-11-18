void __cdecl cross_product(float *u, float *v, float *r)
{
  __m128i v3; // xmm1
  __m128i v4; // xmm1
  __m128i v5; // xmm1

  v3 = (__m128i)*((unsigned int *)u + 2);
  *(float *)v3.m128i_i32 = *(float *)v3.m128i_i32 * v[1];
  *r = (float)(u[1] * v[2]) + COERCE_FLOAT(_mm_cvtsi128_si32(v3) ^ 0x80000000);
  v4 = (__m128i)*(unsigned int *)u;
  *(float *)v4.m128i_i32 = *(float *)v4.m128i_i32 * v[2];
  r[1] = (float)(u[2] * *v) + COERCE_FLOAT(_mm_cvtsi128_si32(v4) ^ 0x80000000);
  v5 = (__m128i)*((unsigned int *)u + 1);
  *(float *)v5.m128i_i32 = *(float *)v5.m128i_i32 * *v;
  r[2] = (float)(*u * v[1]) + COERCE_FLOAT(_mm_cvtsi128_si32(v5) ^ 0x80000000);
}