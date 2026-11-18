void __cdecl OsdGetBezierWeights(float t, float *wP, float *wDP, float *wDP2)
{
  __m128i v4; // xmm1
  float tC2; // [rsp+0h] [rbp-2Ch]
  float t2; // [rsp+8h] [rbp-24h]

  t2 = t * t;
  tC2 = (float)(1.0 - t) * (float)(1.0 - t);
  *wP = tC2 * (float)(1.0 - t);
  wP[1] = (float)(tC2 * t) * 3.0;
  wP[2] = (float)((float)(t * t) * (float)(1.0 - t)) * 3.0;
  wP[3] = (float)(t * t) * t;
  if ( wDP )
  {
    *wDP = -3.0 * tC2;
    v4 = (__m128i)0x41400000u;
    *(float *)v4.m128i_i32 = 12.0 * t;
    wDP[1] = (float)((float)(t2 * 9.0) + COERCE_FLOAT(_mm_cvtsi128_si32(v4) ^ 0x80000000)) + 3.0;
    wDP[2] = (float)(t2 * -9.0) + (float)(6.0 * t);
    wDP[3] = 3.0 * t2;
  }
  if ( wDP2 )
  {
    *wDP2 = 6.0 * (float)(1.0 - t);
    wDP2[1] = (float)(t * 18.0) + -12.0;
    wDP2[2] = (float)(t * -18.0) + 6.0;
    wDP2[3] = 6.0 * t;
  }
}