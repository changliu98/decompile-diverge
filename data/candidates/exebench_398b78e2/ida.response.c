float __cdecl reson(float x, float *a)
{
  float temp; // [rsp+0h] [rbp-14h]

  temp = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)*((unsigned int *)a + 2)) ^ 0x80000000) * a[4])
       + (float)((float)(*a * x) + (float)(a[1] * a[3]));
  a[4] = a[3];
  a[3] = temp;
  return temp;
}