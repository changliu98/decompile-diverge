static __inline__ unsigned int round_to_long(unsigned int x)
{
  return (x & ~3) + (3 - (x & 3));
}