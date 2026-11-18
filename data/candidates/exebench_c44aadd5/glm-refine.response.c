float __cdecl ran2(long *idum)
{
  float result;
  int k;
  int index;

  // Initialization block
  if (*idum <= 0)
  {
    // Ensure idum is positive, with a minimum value of 1
    if (-*idum >= 1)
      *idum = -*idum;
    else
      *idum = 1LL;
      
    ran2_idum2 = *idum;
    
    // Warm up and fill the shuffle table (ran2_iv)
    for (k = 39; k >= 0; --k)
    {
      *idum = 40014 * (*idum % 53668) - 12211 * (*idum / 53668);
      if (*idum < 0)
        *idum += 2147483563LL;
      if (k < 32)
        ran2_iv[k] = *idum;
    }
    ran2_iy = ran2_iv[0];
  }

  // Core LCG 1
  *idum = 40014 * (*idum % 53668) - 12211 * (*idum / 53668);
  if (*idum < 0)
    *idum += 2147483563LL;

  // Core LCG 2
  ran2_idum2 = 40692 * (ran2_idum2 % 52774) - 3791 * (ran2_idum2 / 52774);
  if (ran2_idum2 < 0)
    ran2_idum2 += 0x7FFFFF07uLL; // 2147483391

  // Shuffling and combination
  index = ran2_iy / 67108862;
  ran2_iy = ran2_iv[index] - ran2_idum2;
  ran2_iv[index] = *idum;
  
  if (ran2_iy < 1)
    ran2_iy += 2147483562LL;

  // Convert to float and clamp to upper bound
  result = 4.656613057391769e-10 * (double)(int)ran2_iy;
  if (result > 0.9999997f)
    return 0.9999997f;
    
  return result;
}