double __cdecl ran1(long *idum)
{
  int j;

  // Initialize the generator if the seed is invalid or the state is uninitialized
  if (*idum <= 0 || !ran1_iy)
  {
    // Ensure the seed is positive
    if (*idum >= 0)
      *idum = 1;
    else
      *idum = -*idum;

    // Warm up the generator and fill the shuffle table
    for (j = NTAB + 7; j >= 0; --j)
    {
      // Schrage's algorithm to compute (IA * *idum) % IM without overflow
      *idum = IA * (*idum % IQ) - IR * (*idum / IQ);
      if (*idum < 0)
        *idum += IM;
      
      if (j < NTAB)
        ran1_iv[j] = *idum;
    }
    ran1_iy = ran1_iv[0];
  }

  // Standard generation step using Schrage's algorithm
  *idum = IA * (*idum % IQ) - IR * (*idum / IQ);
  if (*idum < 0)
    *idum += IM;

  // Bays-Durham shuffle
  j = ran1_iy / NDIV;
  ran1_iy = ran1_iv[j];
  ran1_iv[j] = *idum;

  // Return the mapped double, ensuring it doesn't exceed the upper bound
  if (AM * (double)ran1_iy <= RNMX)
    return AM * (double)ran1_iy;
  else
    return RNMX;
}