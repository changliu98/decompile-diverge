static inline unsigned int rotl(unsigned int x)
{
  return (x << 2) + (x >> (32 - 2));
}