unsigned int __cdecl myrnd(unsigned int *seed_ptr, int n)
{
  unsigned int seed = 314159 * *seed_ptr + 1;
  unsigned int val;

  // Fast path: If n is 256, effectively extract the highest byte (seed >> 24).
  // This is semantically identical to HIBYTE(seed) but avoids IDA's macro ambiguity.
  if (n == 256) {
    val = seed >> 24;
  } 
  // Standard path: Modulo reduction for arbitrary ranges.
  else {
    val = seed % n;
  }

  *seed_ptr = seed;
  return val;
}