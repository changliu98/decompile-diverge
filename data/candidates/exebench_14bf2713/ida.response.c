void __cdecl Vector_Cross_Product(float *vectorOut, float *v1, float *v2)
{
  __m128i v3; // xmm1
  __m128i v4; // xmm1
  __m128i v5; // xmm1

  v3 = (__m128i)*((unsigned int *)v1 + 2);
  *(float *)v3.m128i_i32 = *(float *)v3.m128i_i32 * v2[1];
  *vectorOut = (float)(v1[1] * v2[2]) + COERCE_FLOAT(_mm_cvtsi128_si32(v3) ^ 0x80000000);
  v4 = (__m128i)*(unsigned int *)v1;
  *(float *)v4.m128i_i32 = *(float *)v4.m128i_i32 * v2[2];
  vectorOut[1] = (float)(v1[2] * *v2) + COERCE_FLOAT(_mm_cvtsi128_si32(v4) ^ 0x80000000);
  v5 = (__m128i)*((unsigned int *)v1 + 1);
  *(float *)v5.m128i_i32 = *(float *)v5.m128i_i32 * *v2;
  vectorOut[2] = (float)(*v1 * v2[1]) + COERCE_FLOAT(_mm_cvtsi128_si32(v5) ^ 0x80000000);
}