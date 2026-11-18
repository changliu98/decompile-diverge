void __cdecl func0(float *numbers, int size, float *out)
{
  __m128i v3; // xmm0
  float v4; // xmm0_4
  int temp; // [rsp+0h] [rbp-2Ch]
  int j; // [rsp+8h] [rbp-24h]
  int i; // [rsp+Ch] [rbp-20h]
  float min_diff; // [rsp+10h] [rbp-1Ch]

  min_diff = 3.4028235e38;
  *out = *numbers;
  out[1] = numbers[1];
  for ( i = 0; i < size; ++i )
  {
    for ( j = i + 1; j < size; ++j )
    {
      v3 = (__m128i)LODWORD(numbers[i]);
      *(double *)v3.m128i_i64 = (float)(*(float *)v3.m128i_i32 - numbers[j]);
      v4 = *(double *)_mm_and_si128(v3, (__m128i)xmmword_2010).m128i_i64;
      if ( min_diff > v4 )
      {
        min_diff = v4;
        *out = numbers[i];
        out[1] = numbers[j];
      }
    }
  }
  if ( *out > out[1] )
  {
    temp = *(_DWORD *)out;
    *out = out[1];
    *((_DWORD *)out + 1) = temp;
  }
}