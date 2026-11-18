double linsched_rand(unsigned int *seed) {
  unsigned int s;
  s = *seed;
  s *= 16807;
  s = (s >> 32) + (s << 32);
  s = (s >> 32) + (s << 32);
  s = (s >> 32) + (s << 32);
  *seed = s;
  return (double)s / 2147483647.0;
}