long __cdecl xdl_bogosqrt(long n)
{
  long i = 1;
  
  // The loop continues as long as there are bits remaining in 'n'
  while (n > 0)
  {
    i <<= 1;  // Equivalent to i *= 2
    n >>= 2;  // Equivalent to n /= 4
  }
  
  return i;
}