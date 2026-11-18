int __cdecl bbox(int nV, double *vertex, double *dv)
{
  int k; // [rsp+0h] [rbp-6Ch]
  __int64 k3_0; // [rsp+4h] [rbp-68h]
  int k1_0; // [rsp+Ch] [rbp-60h]
  int j; // [rsp+10h] [rbp-5Ch]
  int ja; // [rsp+10h] [rbp-5Ch]
  int i; // [rsp+14h] [rbp-58h]
  int t; // [rsp+18h] [rbp-54h]
  int ta; // [rsp+18h] [rbp-54h]
  double bmax[3]; // [rsp+1Ch] [rbp-50h]
  double bmin[3]; // [rsp+3Ch] [rbp-30h]
  double *dva; // [rsp+54h] [rbp-18h]
  double *vertexa; // [rsp+5Ch] [rbp-10h]
  int nVa; // [rsp+68h] [rbp-4h]

  nVa = nV;
  vertexa = vertex;
  dva = dv;
  for ( j = 0; j < 3; ++j )
  {
    bmin[j] = vertexa[j];
    bmax[j] = vertexa[j];
  }
  for ( i = 1; i < nVa; ++i )
  {
    for ( ja = 0; ja < 3; ++ja )
    {
      if ( bmin[ja] > vertexa[3 * i + ja] )
        bmin[ja] = vertexa[3 * i + ja];
      if ( vertexa[3 * i + ja] > bmax[ja] )
        bmax[ja] = vertexa[3 * i + ja];
    }
  }
  for ( t = 0; t < 3; ++t )
    dva[t] = (bmin[t] + bmax[t]) / 2.0;
  for ( ta = 0; ta < 3; ++ta )
  {
    for ( dva[ta + 3] = 1.0; dva[ta + 3] * (bmax[ta] - bmin[ta]) < 1.0; dva[ta + 3] = 2.0 * dva[ta + 3] )
      ;
    while ( dva[ta + 3] * (bmax[ta] - bmin[ta]) > 1.0 )
      dva[ta + 3] = dva[ta + 3] / 2.0;
  }
  k1_0 = 3;
  k3_0 = 0x400000005LL;
  if ( dva[3] > dva[4] )
  {
    k1_0 = 4;
    HIDWORD(k3_0) = 3;
  }
  if ( dva[SHIDWORD(k3_0)] > dva[5] )
    k3_0 = HIDWORD(k3_0) | 0x500000000LL;
  if ( dva[k1_0] > dva[SHIDWORD(k3_0)] )
  {
    k = k1_0;
    k1_0 = HIDWORD(k3_0);
    HIDWORD(k3_0) = k;
  }
  if ( dva[SHIDWORD(k3_0)] > dva[k1_0] )
    dva[k1_0] = dva[SHIDWORD(k3_0)] / 1.0;
  if ( dva[(int)k3_0] > dva[SHIDWORD(k3_0)] )
    dva[(int)k3_0] = 1.0 * dva[SHIDWORD(k3_0)];
  return 0;
}