void __cdecl geom_matinv4f(float *m)
{
  float v1; // [rsp+0h] [rbp-28h]
  unsigned int v2; // [rsp+4h] [rbp-24h]
  float v3; // [rsp+8h] [rbp-20h]
  unsigned int k; // [rsp+10h] [rbp-18h]
  unsigned int ka; // [rsp+10h] [rbp-18h]
  unsigned int kb; // [rsp+10h] [rbp-18h]
  unsigned int kc; // [rsp+10h] [rbp-18h]
  unsigned int kd; // [rsp+10h] [rbp-18h]
  unsigned int j; // [rsp+14h] [rbp-14h]
  unsigned int ja; // [rsp+14h] [rbp-14h]
  unsigned int jb; // [rsp+14h] [rbp-14h]
  unsigned int jc; // [rsp+14h] [rbp-14h]
  unsigned int jd; // [rsp+14h] [rbp-14h]
  unsigned int i; // [rsp+18h] [rbp-10h]
  unsigned int ia; // [rsp+18h] [rbp-10h]
  unsigned int ib; // [rsp+18h] [rbp-10h]
  unsigned int ic; // [rsp+18h] [rbp-10h]
  unsigned int id; // [rsp+18h] [rbp-10h]
  float sum; // [rsp+1Ch] [rbp-Ch]
  float suma; // [rsp+1Ch] [rbp-Ch]
  float sumb; // [rsp+1Ch] [rbp-Ch]
  float sumc; // [rsp+1Ch] [rbp-Ch]
  float sumd; // [rsp+1Ch] [rbp-Ch]

  for ( i = 1; i < 4; ++i )
    m[4 * i] = m[4 * i] / *m;
  for ( ia = 1; ia < 4; ++ia )
  {
    for ( j = ia; j < 4; ++j )
    {
      sum = 0.0;
      for ( k = 0; k < ia; ++k )
        sum = (float)(m[4 * k + j] * m[4 * ia + k]) + sum;
      m[4 * ia + j] = m[4 * ia + j] - sum;
    }
    if ( ia != 3 )
    {
      for ( ja = ia + 1; ja < 4; ++ja )
      {
        suma = 0.0;
        for ( ka = 0; ka < ia; ++ka )
          suma = (float)(m[4 * ka + ia] * m[4 * ja + ka]) + suma;
        m[4 * ja + ia] = (float)(m[4 * ja + ia] - suma) / m[5 * ia];
      }
    }
  }
  for ( ib = 0; ib < 4; ++ib )
  {
    for ( jb = ib; jb < 4; ++jb )
    {
      sumb = 1.0;
      if ( ib != jb )
      {
        sumb = 0.0;
        for ( kb = ib; kb < jb; ++kb )
          sumb = (float)(COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)LODWORD(m[4 * kb + jb])) ^ 0x80000000) * m[4 * ib + kb])
               + sumb;
      }
      m[4 * ib + jb] = sumb / m[5 * jb];
    }
  }
  for ( ic = 0; ic < 4; ++ic )
  {
    for ( jc = ic; jc < 4; ++jc )
    {
      if ( ic != jc )
      {
        sumc = 0.0;
        for ( kc = ic; kc < jc; ++kc )
        {
          if ( ic == kc )
            v3 = 1.0;
          else
            v3 = m[4 * kc + ic];
          sumc = (float)(m[4 * jc + kc] * v3) + sumc;
        }
        LODWORD(m[4 * jc + ic]) = _mm_cvtsi128_si32((__m128i)LODWORD(sumc)) ^ 0x80000000;
      }
    }
  }
  for ( id = 0; id < 4; ++id )
  {
    for ( jd = 0; jd < 4; ++jd )
    {
      sumd = 0.0;
      if ( id <= jd )
        v2 = jd;
      else
        v2 = id;
      for ( kd = v2; kd < 4; ++kd )
      {
        if ( jd == kd )
          v1 = 1.0;
        else
          v1 = m[4 * kd + jd];
        sumd = (float)(v1 * m[4 * id + kd]) + sumd;
      }
      m[4 * id + jd] = sumd;
    }
  }
}