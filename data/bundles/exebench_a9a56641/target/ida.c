void __cdecl Mat4_inv_Mat4_affine_mul(float *result, float *src1, float *src2)
{
  __m128i v3; // xmm0
  __m128i v4; // xmm0
  __m128i v5; // xmm0
  float v; // [rsp+0h] [rbp-6Ch]
  float v_4; // [rsp+4h] [rbp-68h]
  float t_res_4; // [rsp+10h] [rbp-5Ch]
  float t_res_8; // [rsp+14h] [rbp-58h]
  float t_res_16; // [rsp+1Ch] [rbp-50h]
  float t_res_20; // [rsp+20h] [rbp-4Ch]
  float t_res_24; // [rsp+24h] [rbp-48h]
  float t_res_32; // [rsp+2Ch] [rbp-40h]
  float t_res_36; // [rsp+30h] [rbp-3Ch]
  float t_res_40; // [rsp+34h] [rbp-38h]
  float t_res_48; // [rsp+3Ch] [rbp-30h]
  float t_res_52; // [rsp+40h] [rbp-2Ch]
  float t_res_56; // [rsp+44h] [rbp-28h]

  v3 = (__m128i)*((unsigned int *)src1 + 2);
  *(float *)v3.m128i_i32 = (float)(*(float *)v3.m128i_i32 * src1[14])
                         + (float)((float)(*src1 * src1[12]) + (float)(src1[1] * src1[13]));
  LODWORD(v) = _mm_cvtsi128_si32(v3) ^ 0x80000000;
  v4 = (__m128i)*((unsigned int *)src1 + 6);
  *(float *)v4.m128i_i32 = (float)(*(float *)v4.m128i_i32 * src1[14])
                         + (float)((float)(src1[4] * src1[12]) + (float)(src1[5] * src1[13]));
  LODWORD(v_4) = _mm_cvtsi128_si32(v4) ^ 0x80000000;
  v5 = (__m128i)*((unsigned int *)src1 + 10);
  *(float *)v5.m128i_i32 = (float)(*(float *)v5.m128i_i32 * src1[14])
                         + (float)((float)(src1[8] * src1[12]) + (float)(src1[9] * src1[13]));
  t_res_4 = (float)(src1[6] * src2[2]) + (float)((float)(src1[4] * *src2) + (float)(src1[5] * src2[1]));
  t_res_8 = (float)(src1[10] * src2[2]) + (float)((float)(src1[8] * *src2) + (float)(src1[9] * src2[1]));
  t_res_16 = (float)(src1[2] * src2[6]) + (float)((float)(*src1 * src2[4]) + (float)(src1[1] * src2[5]));
  t_res_20 = (float)(src1[6] * src2[6]) + (float)((float)(src1[4] * src2[4]) + (float)(src1[5] * src2[5]));
  t_res_24 = (float)(src1[10] * src2[6]) + (float)((float)(src1[8] * src2[4]) + (float)(src1[9] * src2[5]));
  t_res_32 = (float)(src1[2] * src2[10]) + (float)((float)(*src1 * src2[8]) + (float)(src1[1] * src2[9]));
  t_res_36 = (float)(src1[6] * src2[10]) + (float)((float)(src1[4] * src2[8]) + (float)(src1[5] * src2[9]));
  t_res_40 = (float)(src1[10] * src2[10]) + (float)((float)(src1[8] * src2[8]) + (float)(src1[9] * src2[9]));
  t_res_48 = (float)(src1[2] * src2[14]) + (float)((float)(src1[1] * src2[13]) + (float)((float)(*src1 * src2[12]) + v));
  t_res_52 = (float)(src1[6] * src2[14])
           + (float)((float)(src1[5] * src2[13]) + (float)((float)(src1[4] * src2[12]) + v_4));
  t_res_56 = (float)(src1[10] * src2[14])
           + (float)((float)(src1[9] * src2[13])
                   + (float)((float)(src1[8] * src2[12]) + COERCE_FLOAT(_mm_cvtsi128_si32(v5) ^ 0x80000000)));
  *result = (float)(src1[2] * src2[2]) + (float)((float)(*src1 * *src2) + (float)(src1[1] * src2[1]));
  result[1] = t_res_4;
  result[2] = t_res_8;
  result[3] = 0.0;
  result[4] = t_res_16;
  result[5] = t_res_20;
  result[6] = t_res_24;
  result[7] = 0.0;
  result[8] = t_res_32;
  result[9] = t_res_36;
  result[10] = t_res_40;
  result[11] = 0.0;
  result[12] = t_res_48;
  result[13] = t_res_52;
  result[14] = t_res_56;
  result[15] = 1.0;
}