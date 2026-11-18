void __cdecl crossproduct(float *result, float *vec, float *vec2)
{
  __m128i v3; // xmm1
  __m128i v4; // xmm1
  __m128i v5; // xmm1

  v3 = (__m128i)*((unsigned int *)vec2 + 2);
  *(float *)v3.m128i_i32 = *(float *)v3.m128i_i32 * vec[1];
  *result = (float)(vec2[1] * vec[2]) + COERCE_FLOAT(_mm_cvtsi128_si32(v3) ^ 0x80000000);
  v4 = (__m128i)*(unsigned int *)vec2;
  *(float *)v4.m128i_i32 = *(float *)v4.m128i_i32 * vec[2];
  result[1] = (float)(vec2[2] * *vec) + COERCE_FLOAT(_mm_cvtsi128_si32(v4) ^ 0x80000000);
  v5 = (__m128i)*((unsigned int *)vec2 + 1);
  *(float *)v5.m128i_i32 = *(float *)v5.m128i_i32 * *vec;
  result[2] = (float)(*vec2 * vec[1]) + COERCE_FLOAT(_mm_cvtsi128_si32(v5) ^ 0x80000000);
}