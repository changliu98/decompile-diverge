void __cdecl vec3CrossProduct(float *vec, const float *lhs, const float *rhs)
{
  __m128i v3; // xmm1
  __m128i v4; // xmm1
  __m128i v5; // xmm1

  v3 = (__m128i)*((unsigned int *)lhs + 2);
  *(float *)v3.m128i_i32 = *(float *)v3.m128i_i32 * rhs[1];
  *vec = (float)(lhs[1] * rhs[2]) + COERCE_FLOAT(_mm_cvtsi128_si32(v3) ^ 0x80000000);
  v4 = (__m128i)*(unsigned int *)lhs;
  *(float *)v4.m128i_i32 = *(float *)v4.m128i_i32 * rhs[2];
  vec[1] = (float)(lhs[2] * *rhs) + COERCE_FLOAT(_mm_cvtsi128_si32(v4) ^ 0x80000000);
  v5 = (__m128i)*((unsigned int *)lhs + 1);
  *(float *)v5.m128i_i32 = *(float *)v5.m128i_i32 * *rhs;
  vec[2] = (float)(*lhs * rhs[1]) + COERCE_FLOAT(_mm_cvtsi128_si32(v5) ^ 0x80000000);
}