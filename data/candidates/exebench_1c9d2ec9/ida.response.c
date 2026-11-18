void __cdecl OsdGetBSplineWeights(float t, float *wP, float *wDP, float *wDP2)
{
  __m128i v4; // xmm1
  float t3; // [rsp+0h] [rbp-2Ch]
  float t2; // [rsp+4h] [rbp-28h]

  t2 = t * t;
  t3 = t * (float)(t * t);
  *wP = 0.16666667 * (float)((float)((float)((float)(t - (float)(t * t)) * -3.0) + 1.0) - t3);
  wP[1] = 0.16666667 * (float)((float)(t3 * 3.0) + (float)((float)((float)(t * t) * -6.0) + 4.0));
  wP[2] = 0.16666667 * (float)((float)((float)((float)(t + (float)(t * t)) - t3) * 3.0) + 1.0);
  wP[3] = 0.16666667 * t3;
  if ( wDP )
  {
    *wDP = (float)((float)(t2 * -0.5) + t) - 0.5;
    v4 = (__m128i)0x40000000u;
    *(float *)v4.m128i_i32 = 2.0 * t;
    wDP[1] = (float)(t2 * 1.5) + COERCE_FLOAT(_mm_cvtsi128_si32(v4) ^ 0x80000000);
    wDP[2] = (float)((float)(t2 * -1.5) + t) + 0.5;
    wDP[3] = 0.5 * t2;
  }
  if ( wDP2 )
  {
    *wDP2 = COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)LODWORD(t)) ^ 0x80000000) + 1.0;
    wDP2[1] = (float)(t * 3.0) + -2.0;
    wDP2[2] = (float)(t * -3.0) + 1.0;
    wDP2[3] = t;
  }
}