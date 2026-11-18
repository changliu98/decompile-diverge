// local variable allocation has failed, the output may be wrong!
void __cdecl quaternionComposition(
        float q01,
        float q02,
        float q03,
        float q04,
        float q11,
        float q12,
        float q13,
        float q14,
        float *q21,
        float *q22,
        float *q23,
        float *q24)
{
  __m128i v12; // xmm1
  __m128i v13; // xmm1
  float q02a; // [rsp+38h] [rbp-8h]

  q02a = q02;
  *(_OWORD *)&q02 = LODWORD(q02);
  *(float *)v12.m128i_i32 = q02 * q12;
  *q21 = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)LODWORD(q04)) ^ 0x80000000) * q14)
       + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)LODWORD(q03)) ^ 0x80000000) * q13)
               + (float)((float)(q01 * q11) + COERCE_FLOAT(_mm_cvtsi128_si32(v12) ^ 0x80000000)));
  *q22 = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)LODWORD(q04)) ^ 0x80000000) * q13)
       + (float)((float)(q03 * q14) + (float)((float)(q01 * q12) + (float)(q02a * q11)));
  v13 = (__m128i)LODWORD(q02a);
  *(float *)v13.m128i_i32 = q02a * q14;
  *q23 = (float)(q04 * q12)
       + (float)((float)(q03 * q11) + (float)((float)(q01 * q13) + COERCE_FLOAT(_mm_cvtsi128_si32(v13) ^ 0x80000000)));
  *q24 = (float)(q04 * q11)
       + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)LODWORD(q03)) ^ 0x80000000) * q12)
               + (float)((float)(q01 * q14) + (float)(q02a * q13)));
}