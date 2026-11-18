void __cdecl func0(int r, int g, int b, double *h, double *s, double *v)
{
  __m128i v6; // xmm1
  __m128i v7; // xmm2
  __m128i v8; // xmm2
  __m128i v9; // xmm0
  __m128i v10; // xmm1
  __m128i v11; // xmm1
  __m128i v12; // xmm2
  __m128i v13; // xmm2
  __m128i v14; // xmm1
  double df_0; // [rsp+8h] [rbp-58h]
  double mx; // [rsp+18h] [rbp-48h]
  double bd; // [rsp+20h] [rbp-40h]
  double gd; // [rsp+28h] [rbp-38h]
  double rd; // [rsp+30h] [rbp-30h]

  rd = (double)r / 255.0;
  gd = (double)g / 255.0;
  bd = (double)b / 255.0;
  v6 = (__m128i)*(unsigned __int64 *)&bd;
  v7 = (__m128i)_mm_cmpunord_sd((__m128d)*(unsigned __int64 *)&gd, (__m128d)*(unsigned __int64 *)&gd);
  *(double *)v6.m128i_i64 = fmax(bd, gd);
  v8 = _mm_or_si128(_mm_andnot_si128(v7, v6), _mm_and_si128(v7, (__m128i)*(unsigned __int64 *)&bd));
  v9 = (__m128i)_mm_cmpunord_sd((__m128d)*(unsigned __int64 *)&rd, (__m128d)*(unsigned __int64 *)&rd);
  v10 = _mm_and_si128(v9, v8);
  *(double *)v8.m128i_i64 = fmax(*(double *)v8.m128i_i64, rd);
  mx = *(double *)_mm_or_si128(_mm_andnot_si128(v9, v8), v10).m128i_i64;
  v11 = (__m128i)*(unsigned __int64 *)&bd;
  v12 = (__m128i)_mm_cmpunord_sd((__m128d)*(unsigned __int64 *)&gd, (__m128d)*(unsigned __int64 *)&gd);
  *(double *)v11.m128i_i64 = fmin(bd, gd);
  v13 = _mm_or_si128(_mm_andnot_si128(v12, v11), _mm_and_si128(v12, (__m128i)*(unsigned __int64 *)&bd));
  v14 = _mm_and_si128(v9, v13);
  *(double *)v13.m128i_i64 = fmin(*(double *)v13.m128i_i64, rd);
  df_0 = mx - *(double *)_mm_or_si128(_mm_andnot_si128(v9, v13), v14).m128i_i64;
  *h = 0.0;
  if ( df_0 > 0.0 )
  {
    if ( mx == rd )
    {
      *h = fmod((gd - bd) / df_0 * 60.0 + 360.0, 360.0);
    }
    else if ( mx == gd )
    {
      *h = fmod((bd - rd) / df_0 * 60.0 + 120.0, 360.0);
    }
    else if ( mx == bd )
    {
      *h = fmod((rd - gd) / df_0 * 60.0 + 240.0, 360.0);
    }
  }
  if ( mx == 0.0 )
    *s = 0.0;
  else
    *s = df_0 / mx * 100.0;
  *v = 100.0 * mx;
}