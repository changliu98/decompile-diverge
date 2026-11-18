void __cdecl qtomat(float *q, float *rot)
{
  __m128i v2; // xmm0
  __m128i v3; // xmm1
  __m128i v4; // xmm0
  __m128i v5; // xmm0
  __m128i v6; // xmm1

  *rot = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)*((unsigned int *)q + 3)) ^ 0x80000000) * q[3])
       + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)*((unsigned int *)q + 2)) ^ 0x80000000) * q[2])
               + (float)((float)(*q * *q) + (float)(q[1] * q[1])));
  v2 = (__m128i)*(unsigned int *)q;
  *(float *)v2.m128i_i32 = *(float *)v2.m128i_i32 * q[3];
  rot[1] = 2.0 * (float)((float)(q[1] * q[2]) + COERCE_FLOAT(_mm_cvtsi128_si32(v2) ^ 0x80000000));
  rot[2] = 2.0 * (float)((float)(q[1] * q[3]) + (float)(*q * q[2]));
  rot[3] = 2.0 * (float)((float)(q[1] * q[2]) + (float)(*q * q[3]));
  v3 = (__m128i)*((unsigned int *)q + 1);
  *(float *)v3.m128i_i32 = *(float *)v3.m128i_i32 * q[1];
  rot[4] = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)*((unsigned int *)q + 3)) ^ 0x80000000) * q[3])
         + (float)((float)(q[2] * q[2]) + (float)((float)(*q * *q) + COERCE_FLOAT(_mm_cvtsi128_si32(v3) ^ 0x80000000)));
  v4 = (__m128i)*(unsigned int *)q;
  *(float *)v4.m128i_i32 = *(float *)v4.m128i_i32 * q[1];
  rot[5] = 2.0 * (float)((float)(q[2] * q[3]) + COERCE_FLOAT(_mm_cvtsi128_si32(v4) ^ 0x80000000));
  v5 = (__m128i)*(unsigned int *)q;
  *(float *)v5.m128i_i32 = *(float *)v5.m128i_i32 * q[2];
  rot[6] = 2.0 * (float)((float)(q[1] * q[3]) + COERCE_FLOAT(_mm_cvtsi128_si32(v5) ^ 0x80000000));
  rot[7] = 2.0 * (float)((float)(q[2] * q[3]) + (float)(*q * q[1]));
  v6 = (__m128i)*((unsigned int *)q + 1);
  *(float *)v6.m128i_i32 = *(float *)v6.m128i_i32 * q[1];
  rot[8] = (float)(q[3] * q[3])
         + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)*((unsigned int *)q + 2)) ^ 0x80000000) * q[2])
                 + (float)((float)(*q * *q) + COERCE_FLOAT(_mm_cvtsi128_si32(v6) ^ 0x80000000)));
}