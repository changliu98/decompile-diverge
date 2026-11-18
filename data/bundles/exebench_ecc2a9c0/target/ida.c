unsigned int __cdecl myrnd(unsigned int *seed_ptr, int n)
{
  unsigned int val; // [rsp+0h] [rbp-14h]
  unsigned int seed; // [rsp+4h] [rbp-10h]

  seed = 314159 * *seed_ptr + 1;
  if ( n == 256 )
    val = HIBYTE(seed);
  else
    val = seed % n;
  *seed_ptr = seed;
  return val;
}