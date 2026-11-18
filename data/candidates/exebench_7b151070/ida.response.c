void __cdecl Mat4_RotateQuaternion(float *mat, float *q)
{
  __m128i v2; // xmm1
  __m128i v3; // xmm1
  __m128i v4; // xmm1
  __m128i v5; // xmm1
  __m128i v6; // xmm1
  __m128i v7; // xmm1
  unsigned int buf; // [rsp+0h] [rbp-40h]
  unsigned int bufa; // [rsp+0h] [rbp-40h]
  unsigned int bufb; // [rsp+0h] [rbp-40h]
  unsigned int buf_4; // [rsp+4h] [rbp-3Ch]
  unsigned int buf_4a; // [rsp+4h] [rbp-3Ch]
  unsigned int buf_4b; // [rsp+4h] [rbp-3Ch]
  unsigned int buf_8; // [rsp+8h] [rbp-38h]
  unsigned int buf_8a; // [rsp+8h] [rbp-38h]
  unsigned int buf_8b; // [rsp+8h] [rbp-38h]
  float buf_12; // [rsp+Ch] [rbp-34h]
  float buf_12a; // [rsp+Ch] [rbp-34h]
  float buf_12b; // [rsp+Ch] [rbp-34h]
  float qt; // [rsp+20h] [rbp-20h]
  float qt_4; // [rsp+24h] [rbp-1Ch]
  float qt_8; // [rsp+28h] [rbp-18h]
  float qt_12; // [rsp+2Ch] [rbp-14h]

  LODWORD(qt) = _mm_cvtsi128_si32((__m128i)*(unsigned int *)q) ^ 0x80000000;
  LODWORD(qt_4) = _mm_cvtsi128_si32((__m128i)*((unsigned int *)q + 1)) ^ 0x80000000;
  LODWORD(qt_8) = _mm_cvtsi128_si32((__m128i)*((unsigned int *)q + 2)) ^ 0x80000000;
  qt_12 = q[3];
  *(float *)&buf = (float)(qt_8 * mat[1])
                 + (float)((float)(q[1] * mat[2]) + (float)((float)(qt_12 * *mat) + (float)(*q * mat[3])));
  *(float *)&buf_4 = (float)(qt * mat[2])
                   + (float)((float)(q[2] * *mat) + (float)((float)(qt_12 * mat[1]) + (float)(q[1] * mat[3])));
  *(float *)&buf_8 = (float)(qt_4 * *mat)
                   + (float)((float)(*q * mat[1]) + (float)((float)(qt_12 * mat[2]) + (float)(q[2] * mat[3])));
  v2 = (__m128i)*(unsigned int *)q;
  *(float *)v2.m128i_i32 = *(float *)v2.m128i_i32 * *mat;
  buf_12 = (float)(qt_8 * mat[2])
         + (float)((float)(qt_4 * mat[1])
                 + (float)((float)(qt_12 * mat[3]) + COERCE_FLOAT(_mm_cvtsi128_si32(v2) ^ 0x80000000)));
  *mat = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)buf_8) ^ 0x80000000) * qt_4)
       + (float)((float)(*(float *)&buf_4 * qt_8) + (float)((float)(buf_12 * qt) + (float)(*(float *)&buf * qt_12)));
  mat[1] = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)buf) ^ 0x80000000) * qt_8)
         + (float)((float)(*(float *)&buf_8 * qt) + (float)((float)(buf_12 * qt_4) + (float)(*(float *)&buf_4 * qt_12)));
  mat[2] = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)buf_4) ^ 0x80000000) * qt)
         + (float)((float)(*(float *)&buf * qt_4) + (float)((float)(buf_12 * qt_8) + (float)(*(float *)&buf_8 * qt_12)));
  v3 = (__m128i)buf;
  *(float *)v3.m128i_i32 = *(float *)&buf * qt;
  mat[3] = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)buf_8) ^ 0x80000000) * qt_8)
         + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)buf_4) ^ 0x80000000) * qt_4)
                 + (float)((float)(buf_12 * qt_12) + COERCE_FLOAT(_mm_cvtsi128_si32(v3) ^ 0x80000000)));
  mat[3] = 0.0;
  *(float *)&bufa = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)*((unsigned int *)q + 2)) ^ 0x80000000) * mat[5])
                  + (float)((float)(q[1] * mat[6]) + (float)((float)(q[3] * mat[4]) + (float)(*q * mat[7])));
  *(float *)&buf_4a = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)*(unsigned int *)q) ^ 0x80000000) * mat[6])
                    + (float)((float)(q[2] * mat[4]) + (float)((float)(q[3] * mat[5]) + (float)(q[1] * mat[7])));
  *(float *)&buf_8a = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)*((unsigned int *)q + 1)) ^ 0x80000000) * mat[4])
                    + (float)((float)(*q * mat[5]) + (float)((float)(q[3] * mat[6]) + (float)(q[2] * mat[7])));
  v4 = (__m128i)*(unsigned int *)q;
  *(float *)v4.m128i_i32 = *(float *)v4.m128i_i32 * mat[4];
  buf_12a = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)*((unsigned int *)q + 2)) ^ 0x80000000) * mat[6])
          + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)*((unsigned int *)q + 1)) ^ 0x80000000) * mat[5])
                  + (float)((float)(q[3] * mat[7]) + COERCE_FLOAT(_mm_cvtsi128_si32(v4) ^ 0x80000000)));
  mat[4] = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)buf_8a) ^ 0x80000000) * qt_4)
         + (float)((float)(*(float *)&buf_4a * qt_8) + (float)((float)(buf_12a * qt) + (float)(*(float *)&bufa * qt_12)));
  mat[5] = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)bufa) ^ 0x80000000) * qt_8)
         + (float)((float)(*(float *)&buf_8a * qt)
                 + (float)((float)(buf_12a * qt_4) + (float)(*(float *)&buf_4a * qt_12)));
  mat[6] = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)buf_4a) ^ 0x80000000) * qt)
         + (float)((float)(*(float *)&bufa * qt_4)
                 + (float)((float)(buf_12a * qt_8) + (float)(*(float *)&buf_8a * qt_12)));
  v5 = (__m128i)bufa;
  *(float *)v5.m128i_i32 = *(float *)&bufa * qt;
  mat[7] = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)buf_8a) ^ 0x80000000) * qt_8)
         + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)buf_4a) ^ 0x80000000) * qt_4)
                 + (float)((float)(buf_12a * qt_12) + COERCE_FLOAT(_mm_cvtsi128_si32(v5) ^ 0x80000000)));
  mat[7] = 0.0;
  *(float *)&bufb = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)*((unsigned int *)q + 2)) ^ 0x80000000) * mat[9])
                  + (float)((float)(q[1] * mat[10]) + (float)((float)(q[3] * mat[8]) + (float)(*q * mat[11])));
  *(float *)&buf_4b = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)*(unsigned int *)q) ^ 0x80000000) * mat[10])
                    + (float)((float)(q[2] * mat[8]) + (float)((float)(q[3] * mat[9]) + (float)(q[1] * mat[11])));
  *(float *)&buf_8b = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)*((unsigned int *)q + 1)) ^ 0x80000000) * mat[8])
                    + (float)((float)(*q * mat[9]) + (float)((float)(q[3] * mat[10]) + (float)(q[2] * mat[11])));
  v6 = (__m128i)*(unsigned int *)q;
  *(float *)v6.m128i_i32 = *(float *)v6.m128i_i32 * mat[8];
  buf_12b = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)*((unsigned int *)q + 2)) ^ 0x80000000) * mat[10])
          + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)*((unsigned int *)q + 1)) ^ 0x80000000) * mat[9])
                  + (float)((float)(q[3] * mat[11]) + COERCE_FLOAT(_mm_cvtsi128_si32(v6) ^ 0x80000000)));
  mat[8] = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)buf_8b) ^ 0x80000000) * qt_4)
         + (float)((float)(*(float *)&buf_4b * qt_8) + (float)((float)(buf_12b * qt) + (float)(*(float *)&bufb * qt_12)));
  mat[9] = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)bufb) ^ 0x80000000) * qt_8)
         + (float)((float)(*(float *)&buf_8b * qt)
                 + (float)((float)(buf_12b * qt_4) + (float)(*(float *)&buf_4b * qt_12)));
  mat[10] = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)buf_4b) ^ 0x80000000) * qt)
          + (float)((float)(*(float *)&bufb * qt_4)
                  + (float)((float)(buf_12b * qt_8) + (float)(*(float *)&buf_8b * qt_12)));
  v7 = (__m128i)bufb;
  *(float *)v7.m128i_i32 = *(float *)&bufb * qt;
  mat[11] = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)buf_8b) ^ 0x80000000) * qt_8)
          + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)buf_4b) ^ 0x80000000) * qt_4)
                  + (float)((float)(buf_12b * qt_12) + COERCE_FLOAT(_mm_cvtsi128_si32(v7) ^ 0x80000000)));
  mat[11] = 0.0;
}