static inline int mt76_incr(int x, int n)
{
  return (x + 1) & (n - 1);
}