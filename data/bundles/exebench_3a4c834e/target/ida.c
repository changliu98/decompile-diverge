void __cdecl drmp3_L3_idct3(float x0, float x1, float x2, float *dst)
{
  float a1; // [rsp+0h] [rbp-20h]

  a1 = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)LODWORD(x2)) ^ 0x80000000) * 0.5) + x0;
  dst[1] = x0 + x2;
  *dst = a1 + (float)(0.86602539 * x1);
  dst[2] = a1 - (float)(0.86602539 * x1);
}