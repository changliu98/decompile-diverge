static inline unsigned int swizzle(unsigned int in, unsigned int limit)
{
  unsigned int out = 0;
  while (limit)
  {
    out = (out << 1) | (in & 1);
    in >>= 1;
    limit >>= 1;
  }
  return out;
}