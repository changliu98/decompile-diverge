float __cdecl ran1(long *idum)
{
  float result;
  int index;

  // Initialization block: executed if seed is non-positive or generator hasn't been initialized
  if (*idum <= 0 || !ran1_iy)
  {
    // Ensure the seed is strictly positive
    if (*idum >= -1)
      *idum = 1;       // Fallback to 1 if seed is 0 or -1
    else
      *idum = -*idum;  // Make seed positive

    // Warm-up phase: discard the first 8 iterations to avoid initial correlations
    for (index = 39; index >= 0; --index)
    {
      // Park-Miller minimal standard generator: (a * seed) mod m
      // Using Schrage's algorithm to avoid 32-bit integer overflow:
      // (a * (seed mod q)) - r * (seed div q)
      *idum = 16807 * (*idum % 127773) - 2836 * (*idum / 127773);
      
      // Handle underflow if the result is negative
      if (*idum < 0)
        *idum += 0x7FFFFFFF; // Add 2^31 - 1

      // Fill the shuffle table (ran1_iv) with the first 32 generated values
      if (index < 32)
        ran1_iv[index] = *idum;
    }
    ran1_iy = ran1_iv[0];
  }

  // Main generation step: advance the linear congruential generator
  *idum = 16807 * (*idum % 127773) - 2836 * (*idum / 127773);
  if (*idum < 0)
    *idum += 0x7FFFFFFF;

  // Bays-Durham shuffle: use the top bits of the current output to index into the table
  index = ran1_iy / 0x4000000; // Equivalent to ran1_iy / 67108864 (or ran1_iy >> 26)
  
  // Swap the current LCG output with the selected table entry
  ran1_iy = ran1_iv[index];
  ran1_iv[index] = *idum;

  // Normalize to a float in the range [0, 1)
  // 4.656613057391769e-10 is 1.0 / (2^31 - 1)
  result = 4.656613057391769e-10 * (double)(int)ran1_iy;
  
  // Clamp the maximum value to prevent returning exactly 1.0
  if (result > 0.9999997f)
    return 0.9999997f;
  
  return result;
}