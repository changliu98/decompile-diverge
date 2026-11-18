float __cdecl func0(float *numbers, int size)
{
  __m128i v2; // xmm1
  float v3; // xmm0_4
  int i; // [rsp+0h] [rbp-20h]
  int ia; // [rsp+0h] [rbp-20h]
  float msum; // [rsp+8h] [rbp-18h]
  float sum; // [rsp+10h] [rbp-10h]

  sum = 0.0;
  for ( i = 0; i < size; ++i )
    sum = numbers[i] + sum;
  msum = 0.0;
  for ( ia = 0; ia < size; ++ia )
  {
    *(double *)v2.m128i_i64 = (float)(numbers[ia] - (float)(sum / (float)size));
    v2 = _mm_and_si128(v2, (__m128i)xmmword_2010);
    v3 = msum + *(double *)v2.m128i_i64;
    msum = v3;
  }
  return msum / (float)size;
}