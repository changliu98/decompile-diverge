void __cdecl vec3_cross(float *out, float *a, float *b)
{
  __m128i v3; // xmm1
  __m128i v4; // xmm1
  __m128i v5; // xmm1

  v3 = (__m128i)*((unsigned int *)a + 2);
  *(float *)v3.m128i_i32 = *(float *)v3.m128i_i32 * b[1];
  *out = (float)(a[1] * b[2]) + COERCE_FLOAT(_mm_cvtsi128_si32(v3) ^ 0x80000000);
  v4 = (__m128i)*(unsigned int *)a;
  *(float *)v4.m128i_i32 = *(float *)v4.m128i_i32 * b[2];
  out[1] = (float)(a[2] * *b) + COERCE_FLOAT(_mm_cvtsi128_si32(v4) ^ 0x80000000);
  v5 = (__m128i)*((unsigned int *)a + 1);
  *(float *)v5.m128i_i32 = *(float *)v5.m128i_i32 * *b;
  out[2] = (float)(*a * b[1]) + COERCE_FLOAT(_mm_cvtsi128_si32(v5) ^ 0x80000000);
}