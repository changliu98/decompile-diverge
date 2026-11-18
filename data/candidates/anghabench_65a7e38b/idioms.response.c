static inline int SCALE(long a, int b, int c)
{
  if (a < 0)
    return (b * a - (c / 2)) / c;
  else
    return ((b * a + (c / 2)) / c);
}