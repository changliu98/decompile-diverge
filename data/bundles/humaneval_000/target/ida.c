int __cdecl func0(float *numbers, int size, float threshold)
{
  __m128i v3; // xmm1
  int j; // [rsp+0h] [rbp-20h]
  int i; // [rsp+4h] [rbp-1Ch]

  for ( i = 0; i < size; ++i )
  {
    for ( j = i + 1; j < size; ++j )
    {
      *(double *)v3.m128i_i64 = (float)(numbers[i] - numbers[j]);
      v3 = _mm_and_si128(v3, (__m128i)xmmword_2010);
      if ( threshold > *(double *)v3.m128i_i64 )
        return 1;
    }
  }
  return 0;
}