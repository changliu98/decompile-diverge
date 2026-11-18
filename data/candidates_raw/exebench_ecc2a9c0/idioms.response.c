int nextrand(unsigned int *seed, int n)
{
  unsigned int s = *seed * 314159 + 1;
  int r;
  if (n == 256)
    r = s >> 24;
  else
    r = s % n;
  *seed = s;
  return r;
}