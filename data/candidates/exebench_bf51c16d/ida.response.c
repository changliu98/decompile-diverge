int __cdecl condF(
        int xn,
        float *xp,
        int yn,
        float *yp,
        int ltn,
        float *ltp,
        int eqn,
        float *eqp,
        int gtn,
        float *gtp,
        int rn,
        float *rp)
{
  float v13; // [rsp+0h] [rbp-3Ch]
  float v14; // [rsp+4h] [rbp-38h]
  int k; // [rsp+8h] [rbp-34h]

  if ( xn != yn || xn != ltn || xn != eqn || xn != gtn || xn != rn )
    return 2000;
  for ( k = 0; k < xn; ++k )
  {
    if ( yp[k] <= xp[k] )
    {
      if ( xp[k] <= yp[k] )
        v13 = eqp[k];
      else
        v13 = gtp[k];
      v14 = v13;
    }
    else
    {
      v14 = ltp[k];
    }
    rp[k] = v14;
  }
  return 0;
}