static __inline__ unsigned int frag_num(unsigned int x)
{
  return (x & ~3) + (3 - (x & 3));
}