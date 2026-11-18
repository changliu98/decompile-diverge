void __cdecl mm_us(float *m1, float *m2, float *mout)
{
  float su; // [rsp+0h] [rbp-28h]
  int k; // [rsp+4h] [rbp-24h]
  int j; // [rsp+8h] [rbp-20h]
  int i; // [rsp+Ch] [rbp-1Ch]

  for ( i = 0; i < 4; ++i )
  {
    for ( j = 0; j < 4; ++j )
    {
      su = 0.0;
      for ( k = 0; k < 4; ++k )
        su = (float)(m1[4 * i + k] * m2[4 * k + j]) + su;
      mout[4 * i + j] = su;
    }
  }
}