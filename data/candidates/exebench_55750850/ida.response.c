void __cdecl rotate_point(float *point)
{
  __m128i v1; // xmm1
  __m128i v2; // xmm1
  float temp; // [rsp+10h] [rbp-14h]
  float temp_4; // [rsp+14h] [rbp-10h]
  unsigned int temp_8; // [rsp+18h] [rbp-Ch]

  temp = *point;
  v1 = (__m128i)*((unsigned int *)point + 2);
  *(float *)v1.m128i_i32 = *(float *)v1.m128i_i32 * 0.0174524;
  temp_4 = (float)(point[1] * 0.99984771) + COERCE_FLOAT(_mm_cvtsi128_si32(v1) ^ 0x80000000);
  *(float *)&temp_8 = (float)(point[1] * 0.0174524) + (float)(point[2] * 0.99984771);
  v2 = (__m128i)temp_8;
  *(float *)v2.m128i_i32 = *(float *)&temp_8 * 0.069756471;
  *point = (float)(*point * 0.99756408) + COERCE_FLOAT(_mm_cvtsi128_si32(v2) ^ 0x80000000);
  point[1] = temp_4;
  point[2] = (float)(temp * 0.069756471) + (float)(*(float *)&temp_8 * 0.99756408);
}