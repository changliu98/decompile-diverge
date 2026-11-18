void __cdecl QuaternionMult(float *pfQOut, float *pfQIn1, float *pfQIn2)
{
  __m128i v3; // xmm1
  __m128i v4; // xmm1

  v3 = (__m128i)*((unsigned int *)pfQIn2 + 1);
  *(float *)v3.m128i_i32 = *(float *)v3.m128i_i32 * pfQIn1[1];
  *pfQOut = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)*((unsigned int *)pfQIn2 + 3)) ^ 0x80000000) * pfQIn1[3])
          + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)*((unsigned int *)pfQIn2 + 2)) ^ 0x80000000)
                          * pfQIn1[2])
                  + (float)((float)(*pfQIn2 * *pfQIn1) + COERCE_FLOAT(_mm_cvtsi128_si32(v3) ^ 0x80000000)));
  pfQOut[1] = (float)(pfQIn2[3] * pfQIn1[2])
            + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)*((unsigned int *)pfQIn2 + 2)) ^ 0x80000000)
                            * pfQIn1[3])
                    + (float)((float)(pfQIn2[1] * *pfQIn1) + (float)(*pfQIn2 * pfQIn1[1])));
  pfQOut[2] = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)*((unsigned int *)pfQIn2 + 3)) ^ 0x80000000) * pfQIn1[1])
            + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)*((unsigned int *)pfQIn2 + 2)) ^ 0x80000000)
                            * *pfQIn1)
                    + (float)((float)(*pfQIn2 * pfQIn1[2]) + (float)(pfQIn2[1] * pfQIn1[3])));
  v4 = (__m128i)*((unsigned int *)pfQIn2 + 1);
  *(float *)v4.m128i_i32 = *(float *)v4.m128i_i32 * pfQIn1[2];
  pfQOut[3] = (float)(pfQIn2[3] * *pfQIn1)
            + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)*((unsigned int *)pfQIn2 + 2)) ^ 0x80000000)
                            * pfQIn1[1])
                    + (float)((float)(*pfQIn2 * pfQIn1[3]) + COERCE_FLOAT(_mm_cvtsi128_si32(v4) ^ 0x80000000)));
}