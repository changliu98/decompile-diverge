int __cdecl condF(
        int xn,    float *xp,
        int yn,    float *yp,
        int ltn,   float *ltp,
        int eqn,   float *eqp,
        int gtn,   float *gtp,
        int rn,    float *rp)
{
  // Check if all array lengths are equal
  if (xn != yn || xn != ltn || xn != eqn || xn != gtn || xn != rn)
    return 2000;

  // Iterate over the arrays
  for (int k = 0; k < xn; ++k)
  {
    if (yp[k] > xp[k])
    {
      // yp[k] > xp[k]
      rp[k] = ltp[k];
    }
    else if (xp[k] > yp[k])
    {
      // yp[k] < xp[k]
      rp[k] = gtp[k];
    }
    else
    {
      // yp[k] == xp[k]
      rp[k] = eqp[k];
    }
  }
  
  return 0;
}