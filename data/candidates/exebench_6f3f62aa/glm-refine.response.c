float __cdecl ran1(long *idum)
{
  float result;

  // Initialization branch: triggered on first call or if the seed is <= 0
  if ( *idum <= 0 || !ran1_iy )
  {
    // Ensure the seed is positive (fallback to 1 if it was exactly 0)
    if ( -*idum >= 1 )
      *idum = -*idum;
    else
      *idum = 1LL;
      
    // Warm-up phase: generate 39 values to prime the generator
    for ( int j = 39; j >= 0; --j )
    {
      // Park-Miller Minimal Standard PRNG: (16807 * seed) mod 2147483647
      // Optimized via Schrage's algorithm to avoid 32-bit integer overflow
      *idum = 16807 * (*idum % 127773) - 2836 * (*idum / 127773);
      if ( *idum < 0 )
        *idum += 0x7FFFFFFFLL; // 2147483647
        
      // Fill the shuffle table (ran1_iv) with the last 32 generated values
      if ( j < 32 )
        ran1_iv[j] = *idum;
    }
    ran1_iy = ran1_iv[0];
  }

  // Core PRNG step: generate the next raw random number
  *idum = 16807 * (*idum % 127773) - 2836 * (*idum / 127773);
  if ( *idum < 0 )
    *idum += 0x7FFFFFFFLL;

  // Bays & Knuth shuffle: use the top 6 bits to index into the table
  int ja = ran1_iy / 0x4000000; // Equivalent to ran1_iy >> 25 (dividing by 67108864)
  ran1_iy = ran1_iv[ja];
  ran1_iv[ja] = *idum;

  // Normalize to a float in the range (0.0, 1.0)
  // 4.656612875245797e-10 is 1.0 / 2147483647.0
  result = 4.656612875245797e-10 * (double)(int)ran1_iy;
  
  // Clamp the maximum value to prevent returning exactly 1.0
  if ( result > 0.99999988 )
    return 0.99999988;
    
  return result;
}