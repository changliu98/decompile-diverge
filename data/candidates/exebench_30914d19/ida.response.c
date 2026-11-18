void __cdecl rsVec_cross(float *v, float *vec1, float *vec2)
{
  __m128i v3; // xmm1
  __m128i v4; // xmm1
  __m128i v5; // xmm1

  v3 = (__m128i)*((unsigned int *)vec2 + 1);
  *(float *)v3.m128i_i32 = *(float *)v3.m128i_i32 * vec1[2];
  *v = (float)(vec1[1] * vec2[2]) + COERCE_FLOAT(_mm_cvtsi128_si32(v3) ^ 0x80000000);
  v4 = (__m128i)*((unsigned int *)vec2 + 2);
  *(float *)v4.m128i_i32 = *(float *)v4.m128i_i32 * *vec1;
  v[1] = (float)(vec1[2] * *vec2) + COERCE_FLOAT(_mm_cvtsi128_si32(v4) ^ 0x80000000);
  v5 = (__m128i)*(unsigned int *)vec2;
  *(float *)v5.m128i_i32 = *(float *)v5.m128i_i32 * vec1[1];
  v[2] = (float)(*vec1 * vec2[1]) + COERCE_FLOAT(_mm_cvtsi128_si32(v5) ^ 0x80000000);
}