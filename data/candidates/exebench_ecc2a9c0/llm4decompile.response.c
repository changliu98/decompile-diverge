int myrnd(unsigned int *seed_ptr, int n)
{
  unsigned int seed;
  int result;

  seed = *seed_ptr;
  seed = ((3141592621U * seed) + 1);
  if (n == 256)
    result = (seed >> 24) & 0xFF;
  else
    result = seed % n;
  *seed_ptr = seed;
  return result;
}