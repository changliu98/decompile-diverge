double __cdecl readDummyArray(double *dummy, unsigned __int64 sizeMB)
{
  __m128d v2; // xmm2
  double a; // [rsp+0h] [rbp-28h]
  unsigned __int64 i; // [rsp+8h] [rbp-20h]
  unsigned __int64 end; // [rsp+10h] [rbp-18h] BYREF
  unsigned __int64 sizeMBa; // [rsp+18h] [rbp-10h]
  double *dummya; // [rsp+20h] [rbp-8h]

  dummya = dummy;
  sizeMBa = sizeMB;
  end = sizeMB >> 3;
  a = 0.0;
  for ( i = 0LL; i < end; ++i )
    a = dummya[i] + a;
  v2 = _mm_sub_pd(
         (__m128d)_mm_unpacklo_epi32(_mm_loadl_epi64((const __m128i *)&end), (__m128i)xmmword_2010),
         (__m128d)xmmword_2020);
  *dummya = a / (_mm_unpackhi_pd(v2, v2).m128d_f64[0] + v2.m128d_f64[0]);
  return a;
}