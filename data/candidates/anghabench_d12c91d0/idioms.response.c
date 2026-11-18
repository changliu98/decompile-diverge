static inline unsigned int REG_A5XX_RB_MRT(unsigned int x, int r)
{
  return (x << r) | (x >> (32 - r));
}