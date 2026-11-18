int __cdecl func0(float a, float b, float c)
{
  __m128i v3; // xmm1
  __m128i v4; // xmm1
  __m128i v5; // xmm1
  int v8; // [rsp+Ch] [rbp-4h]

  v3 = (__m128i)LODWORD(a);
  *(double *)v3.m128i_i64 = (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)LODWORD(c)) ^ 0x80000000) * c)
                                  + (float)((float)(a * a) + (float)(b * b)));
  v8 = 1;
  if ( *(double *)_mm_and_si128(v3, (__m128i)xmmword_2010).m128i_i64 >= 0.0001 )
  {
    v4 = (__m128i)LODWORD(a);
    *(double *)v4.m128i_i64 = (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)LODWORD(b)) ^ 0x80000000) * b)
                                    + (float)((float)(a * a) + (float)(c * c)));
    if ( *(double *)_mm_and_si128(v4, (__m128i)xmmword_2010).m128i_i64 >= 0.0001 )
    {
      v5 = (__m128i)LODWORD(b);
      *(double *)v5.m128i_i64 = (float)((float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)LODWORD(a)) ^ 0x80000000) * a)
                                      + (float)((float)(b * b) + (float)(c * c)));
      if ( *(double *)_mm_and_si128(v5, (__m128i)xmmword_2010).m128i_i64 >= 0.0001 )
        return 0;
    }
  }
  return v8;
}