__int64 __cdecl func0(float *lst, int lst_size)
{
  __m128i v2; // xmm1
  int v4; // [rsp+4h] [rbp-2Ch]
  double v5; // [rsp+8h] [rbp-28h]
  int i; // [rsp+14h] [rbp-1Ch]
  __int64 sum; // [rsp+18h] [rbp-18h]

  sum = 0LL;
  for ( i = 0; i < lst_size; ++i )
  {
    v5 = lst[i];
    v2 = (__m128i)*(unsigned __int64 *)&v5;
    *(double *)v2.m128i_i64 = v5 - round(v5);
    if ( *(double *)_mm_and_si128(v2, (__m128i)xmmword_2010).m128i_i64 < 0.0001
      && lst[i] > 0.0
      && (int)round(lst[i]) % 2 == 1 )
    {
      v4 = (int)round(lst[i]);
      sum += (int)round(lst[i]) * v4;
    }
  }
  return sum;
}