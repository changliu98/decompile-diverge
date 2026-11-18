void __cdecl warp_mat4_fill_inverse(float *result, const float *m)
{
  __m128i v2; // xmm1
  float v3; // xmm0_4
  __m128i v4; // xmm1
  __m128i v5; // xmm0
  __m128i v6; // xmm0
  __m128i v7; // xmm1
  __m128i v8; // xmm1
  __m128i v9; // xmm1
  __m128i v10; // xmm0
  __m128i v11; // xmm0
  __m128i v12; // xmm1
  __m128i v13; // xmm0
  __m128i v14; // xmm1
  __m128i v15; // xmm1
  __m128i v16; // xmm1
  __m128i v17; // xmm0
  __m128i v18; // xmm0
  __m128i v19; // xmm1
  __m128i v20; // xmm1
  __m128i v21; // xmm1
  __m128i v22; // xmm0
  __m128i v23; // xmm1
  __m128i v24; // xmm1
  __m128i v25; // xmm0
  __m128i v26; // xmm0
  __m128i v27; // xmm1
  __m128i v28; // xmm1
  __m128i v29; // xmm1
  __m128i v30; // xmm0
  __m128i v31; // xmm0
  __m128i v32; // xmm1
  __m128i v33; // xmm0
  __m128i v34; // xmm1
  __m128i v35; // xmm1
  __m128i v36; // xmm1
  __m128i v37; // xmm0
  __m128i v38; // xmm0
  __m128i v39; // xmm1
  __m128i v40; // xmm1
  __m128i v41; // xmm1
  __m128i v42; // xmm0
  int i; // [rsp+0h] [rbp-58h]
  float det; // [rsp+4h] [rbp-54h]
  float deta; // [rsp+4h] [rbp-54h]
  float inv[16]; // [rsp+8h] [rbp-50h]
  const float *ma; // [rsp+48h] [rbp-10h]
  float *resulta; // [rsp+50h] [rbp-8h]

  resulta = result;
  ma = m;
  v2 = (__m128i)*((unsigned int *)m + 5);
  *(float *)v2.m128i_i32 = (float)(*(float *)v2.m128i_i32 * m[11]) * m[14];
  v3 = (float)((float)(m[5] * m[10]) * m[15]) + COERCE_FLOAT(_mm_cvtsi128_si32(v2) ^ 0x80000000);
  v4 = (__m128i)*((unsigned int *)m + 9);
  *(float *)v4.m128i_i32 = *(float *)v4.m128i_i32 * m[6];
  *(float *)v4.m128i_i32 = (float)((float)(m[13] * m[6]) * m[11])
                         + (float)((float)((float)(m[9] * m[7]) * m[14])
                                 + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32(v4) ^ 0x80000000) * m[15]) + v3));
  v5 = (__m128i)*((unsigned int *)m + 13);
  *(float *)v5.m128i_i32 = *(float *)v5.m128i_i32 * m[7];
  inv[0] = (float)(COERCE_FLOAT(_mm_cvtsi128_si32(v5) ^ 0x80000000) * m[10]) + *(float *)v4.m128i_i32;
  v6 = (__m128i)*((unsigned int *)m + 8);
  *(float *)v6.m128i_i32 = *(float *)v6.m128i_i32 * m[7];
  v7 = (__m128i)*((unsigned int *)m + 12);
  *(float *)v7.m128i_i32 = *(float *)v7.m128i_i32 * m[6];
  inv[4] = (float)((float)(m[12] * m[7]) * m[10])
         + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32(v7) ^ 0x80000000) * m[11])
                 + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32(v6) ^ 0x80000000) * m[14])
                         + (float)((float)((float)(m[8] * m[6]) * m[15])
                                 + (float)((float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)*((unsigned int *)m + 4)) ^ 0x80000000)
                                                         * m[10])
                                                 * m[15])
                                         + (float)((float)(m[4] * m[11]) * m[14])))));
  v8 = (__m128i)*((unsigned int *)m + 4);
  *(float *)v8.m128i_i32 = (float)(*(float *)v8.m128i_i32 * m[11]) * m[13];
  *(float *)v6.m128i_i32 = (float)((float)(m[4] * m[9]) * m[15]) + COERCE_FLOAT(_mm_cvtsi128_si32(v8) ^ 0x80000000);
  v9 = (__m128i)*((unsigned int *)m + 8);
  *(float *)v9.m128i_i32 = *(float *)v9.m128i_i32 * m[5];
  *(float *)v9.m128i_i32 = (float)((float)(m[12] * m[5]) * m[11])
                         + (float)((float)((float)(m[8] * m[7]) * m[13])
                                 + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32(v9) ^ 0x80000000) * m[15])
                                         + *(float *)v6.m128i_i32));
  v10 = (__m128i)*((unsigned int *)m + 12);
  *(float *)v10.m128i_i32 = *(float *)v10.m128i_i32 * m[7];
  inv[8] = (float)(COERCE_FLOAT(_mm_cvtsi128_si32(v10) ^ 0x80000000) * m[9]) + *(float *)v9.m128i_i32;
  v11 = (__m128i)*((unsigned int *)m + 8);
  *(float *)v11.m128i_i32 = *(float *)v11.m128i_i32 * m[6];
  v12 = (__m128i)*((unsigned int *)m + 12);
  *(float *)v12.m128i_i32 = *(float *)v12.m128i_i32 * m[5];
  inv[12] = (float)((float)(m[12] * m[6]) * m[9])
          + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32(v12) ^ 0x80000000) * m[10])
                  + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32(v11) ^ 0x80000000) * m[13])
                          + (float)((float)((float)(m[8] * m[5]) * m[14])
                                  + (float)((float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)*((unsigned int *)m + 4)) ^ 0x80000000)
                                                          * m[9])
                                                  * m[14])
                                          + (float)((float)(m[4] * m[10]) * m[13])))));
  v13 = (__m128i)*((unsigned int *)m + 9);
  *(float *)v13.m128i_i32 = *(float *)v13.m128i_i32 * m[3];
  v14 = (__m128i)*((unsigned int *)m + 13);
  *(float *)v14.m128i_i32 = *(float *)v14.m128i_i32 * m[2];
  inv[1] = (float)((float)(m[13] * m[3]) * m[10])
         + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32(v14) ^ 0x80000000) * m[11])
                 + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32(v13) ^ 0x80000000) * m[14])
                         + (float)((float)((float)(m[9] * m[2]) * m[15])
                                 + (float)((float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)*((unsigned int *)m + 1)) ^ 0x80000000)
                                                         * m[10])
                                                 * m[15])
                                         + (float)((float)(m[1] * m[11]) * m[14])))));
  v15 = (__m128i)*(unsigned int *)m;
  *(float *)v15.m128i_i32 = (float)(*(float *)v15.m128i_i32 * m[11]) * m[14];
  *(float *)v13.m128i_i32 = (float)((float)(*m * m[10]) * m[15]) + COERCE_FLOAT(_mm_cvtsi128_si32(v15) ^ 0x80000000);
  v16 = (__m128i)*((unsigned int *)m + 8);
  *(float *)v16.m128i_i32 = *(float *)v16.m128i_i32 * m[2];
  *(float *)v16.m128i_i32 = (float)((float)(m[12] * m[2]) * m[11])
                          + (float)((float)((float)(m[8] * m[3]) * m[14])
                                  + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32(v16) ^ 0x80000000) * m[15])
                                          + *(float *)v13.m128i_i32));
  v17 = (__m128i)*((unsigned int *)m + 12);
  *(float *)v17.m128i_i32 = *(float *)v17.m128i_i32 * m[3];
  inv[5] = (float)(COERCE_FLOAT(_mm_cvtsi128_si32(v17) ^ 0x80000000) * m[10]) + *(float *)v16.m128i_i32;
  v18 = (__m128i)*((unsigned int *)m + 8);
  *(float *)v18.m128i_i32 = *(float *)v18.m128i_i32 * m[3];
  v19 = (__m128i)*((unsigned int *)m + 12);
  *(float *)v19.m128i_i32 = *(float *)v19.m128i_i32 * m[1];
  inv[9] = (float)((float)(m[12] * m[3]) * m[9])
         + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32(v19) ^ 0x80000000) * m[11])
                 + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32(v18) ^ 0x80000000) * m[13])
                         + (float)((float)((float)(m[8] * m[1]) * m[15])
                                 + (float)((float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)*(unsigned int *)m) ^ 0x80000000)
                                                         * m[9])
                                                 * m[15])
                                         + (float)((float)(*m * m[11]) * m[13])))));
  v20 = (__m128i)*(unsigned int *)m;
  *(float *)v20.m128i_i32 = (float)(*(float *)v20.m128i_i32 * m[10]) * m[13];
  *(float *)v18.m128i_i32 = (float)((float)(*m * m[9]) * m[14]) + COERCE_FLOAT(_mm_cvtsi128_si32(v20) ^ 0x80000000);
  v21 = (__m128i)*((unsigned int *)m + 8);
  *(float *)v21.m128i_i32 = *(float *)v21.m128i_i32 * m[1];
  *(float *)v21.m128i_i32 = (float)((float)(m[12] * m[1]) * m[10])
                          + (float)((float)((float)(m[8] * m[2]) * m[13])
                                  + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32(v21) ^ 0x80000000) * m[14])
                                          + *(float *)v18.m128i_i32));
  v22 = (__m128i)*((unsigned int *)m + 12);
  *(float *)v22.m128i_i32 = *(float *)v22.m128i_i32 * m[2];
  inv[13] = (float)(COERCE_FLOAT(_mm_cvtsi128_si32(v22) ^ 0x80000000) * m[9]) + *(float *)v21.m128i_i32;
  v23 = (__m128i)*((unsigned int *)m + 1);
  *(float *)v23.m128i_i32 = (float)(*(float *)v23.m128i_i32 * m[7]) * m[14];
  *(float *)v22.m128i_i32 = (float)((float)(m[1] * m[6]) * m[15]) + COERCE_FLOAT(_mm_cvtsi128_si32(v23) ^ 0x80000000);
  v24 = (__m128i)*((unsigned int *)m + 5);
  *(float *)v24.m128i_i32 = *(float *)v24.m128i_i32 * m[2];
  *(float *)v24.m128i_i32 = (float)((float)(m[13] * m[2]) * m[7])
                          + (float)((float)((float)(m[5] * m[3]) * m[14])
                                  + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32(v24) ^ 0x80000000) * m[15])
                                          + *(float *)v22.m128i_i32));
  v25 = (__m128i)*((unsigned int *)m + 13);
  *(float *)v25.m128i_i32 = *(float *)v25.m128i_i32 * m[3];
  inv[2] = (float)(COERCE_FLOAT(_mm_cvtsi128_si32(v25) ^ 0x80000000) * m[6]) + *(float *)v24.m128i_i32;
  v26 = (__m128i)*((unsigned int *)m + 4);
  *(float *)v26.m128i_i32 = *(float *)v26.m128i_i32 * m[3];
  v27 = (__m128i)*((unsigned int *)m + 12);
  *(float *)v27.m128i_i32 = *(float *)v27.m128i_i32 * m[2];
  inv[6] = (float)((float)(m[12] * m[3]) * m[6])
         + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32(v27) ^ 0x80000000) * m[7])
                 + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32(v26) ^ 0x80000000) * m[14])
                         + (float)((float)((float)(m[4] * m[2]) * m[15])
                                 + (float)((float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)*(unsigned int *)m) ^ 0x80000000)
                                                         * m[6])
                                                 * m[15])
                                         + (float)((float)(*m * m[7]) * m[14])))));
  v28 = (__m128i)*(unsigned int *)m;
  *(float *)v28.m128i_i32 = (float)(*(float *)v28.m128i_i32 * m[7]) * m[13];
  *(float *)v26.m128i_i32 = (float)((float)(*m * m[5]) * m[15]) + COERCE_FLOAT(_mm_cvtsi128_si32(v28) ^ 0x80000000);
  v29 = (__m128i)*((unsigned int *)m + 4);
  *(float *)v29.m128i_i32 = *(float *)v29.m128i_i32 * m[1];
  *(float *)v29.m128i_i32 = (float)((float)(m[12] * m[1]) * m[7])
                          + (float)((float)((float)(m[4] * m[3]) * m[13])
                                  + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32(v29) ^ 0x80000000) * m[15])
                                          + *(float *)v26.m128i_i32));
  v30 = (__m128i)*((unsigned int *)m + 12);
  *(float *)v30.m128i_i32 = *(float *)v30.m128i_i32 * m[3];
  inv[10] = (float)(COERCE_FLOAT(_mm_cvtsi128_si32(v30) ^ 0x80000000) * m[5]) + *(float *)v29.m128i_i32;
  v31 = (__m128i)*((unsigned int *)m + 4);
  *(float *)v31.m128i_i32 = *(float *)v31.m128i_i32 * m[2];
  v32 = (__m128i)*((unsigned int *)m + 12);
  *(float *)v32.m128i_i32 = *(float *)v32.m128i_i32 * m[1];
  inv[14] = (float)((float)(m[12] * m[2]) * m[5])
          + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32(v32) ^ 0x80000000) * m[6])
                  + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32(v31) ^ 0x80000000) * m[13])
                          + (float)((float)((float)(m[4] * m[1]) * m[14])
                                  + (float)((float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)*(unsigned int *)m) ^ 0x80000000)
                                                          * m[5])
                                                  * m[14])
                                          + (float)((float)(*m * m[6]) * m[13])))));
  v33 = (__m128i)*((unsigned int *)m + 5);
  *(float *)v33.m128i_i32 = *(float *)v33.m128i_i32 * m[3];
  v34 = (__m128i)*((unsigned int *)m + 9);
  *(float *)v34.m128i_i32 = *(float *)v34.m128i_i32 * m[2];
  inv[3] = (float)((float)(m[9] * m[3]) * m[6])
         + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32(v34) ^ 0x80000000) * m[7])
                 + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32(v33) ^ 0x80000000) * m[10])
                         + (float)((float)((float)(m[5] * m[2]) * m[11])
                                 + (float)((float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)*((unsigned int *)m + 1)) ^ 0x80000000)
                                                         * m[6])
                                                 * m[11])
                                         + (float)((float)(m[1] * m[7]) * m[10])))));
  v35 = (__m128i)*(unsigned int *)m;
  *(float *)v35.m128i_i32 = (float)(*(float *)v35.m128i_i32 * m[7]) * m[10];
  *(float *)v33.m128i_i32 = (float)((float)(*m * m[6]) * m[11]) + COERCE_FLOAT(_mm_cvtsi128_si32(v35) ^ 0x80000000);
  v36 = (__m128i)*((unsigned int *)m + 4);
  *(float *)v36.m128i_i32 = *(float *)v36.m128i_i32 * m[2];
  *(float *)v36.m128i_i32 = (float)((float)(m[8] * m[2]) * m[7])
                          + (float)((float)((float)(m[4] * m[3]) * m[10])
                                  + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32(v36) ^ 0x80000000) * m[11])
                                          + *(float *)v33.m128i_i32));
  v37 = (__m128i)*((unsigned int *)m + 8);
  *(float *)v37.m128i_i32 = *(float *)v37.m128i_i32 * m[3];
  inv[7] = (float)(COERCE_FLOAT(_mm_cvtsi128_si32(v37) ^ 0x80000000) * m[6]) + *(float *)v36.m128i_i32;
  v38 = (__m128i)*((unsigned int *)m + 4);
  *(float *)v38.m128i_i32 = *(float *)v38.m128i_i32 * m[3];
  v39 = (__m128i)*((unsigned int *)m + 8);
  *(float *)v39.m128i_i32 = *(float *)v39.m128i_i32 * m[1];
  inv[11] = (float)((float)(m[8] * m[3]) * m[5])
          + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32(v39) ^ 0x80000000) * m[7])
                  + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32(v38) ^ 0x80000000) * m[9])
                          + (float)((float)((float)(m[4] * m[1]) * m[11])
                                  + (float)((float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)*(unsigned int *)m) ^ 0x80000000)
                                                          * m[5])
                                                  * m[11])
                                          + (float)((float)(*m * m[7]) * m[9])))));
  v40 = (__m128i)*(unsigned int *)m;
  *(float *)v40.m128i_i32 = (float)(*(float *)v40.m128i_i32 * m[6]) * m[9];
  *(float *)v38.m128i_i32 = (float)((float)(*m * m[5]) * m[10]) + COERCE_FLOAT(_mm_cvtsi128_si32(v40) ^ 0x80000000);
  v41 = (__m128i)*((unsigned int *)m + 4);
  *(float *)v41.m128i_i32 = *(float *)v41.m128i_i32 * m[1];
  *(float *)v41.m128i_i32 = (float)((float)(m[8] * m[1]) * m[6])
                          + (float)((float)((float)(m[4] * m[2]) * m[9])
                                  + (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32(v41) ^ 0x80000000) * m[10])
                                          + *(float *)v38.m128i_i32));
  v42 = (__m128i)*((unsigned int *)m + 8);
  *(float *)v42.m128i_i32 = *(float *)v42.m128i_i32 * m[2];
  inv[15] = (float)(COERCE_FLOAT(_mm_cvtsi128_si32(v42) ^ 0x80000000) * m[5]) + *(float *)v41.m128i_i32;
  det = (float)(m[3] * inv[12])
      + (float)((float)(m[2] * inv[8]) + (float)((float)(*m * inv[0]) + (float)(m[1] * inv[4])));
  if ( det != 0.0 )
  {
    deta = 1.0 / det;
    for ( i = 0; i < 16; ++i )
      resulta[i] = inv[i] * deta;
  }
}