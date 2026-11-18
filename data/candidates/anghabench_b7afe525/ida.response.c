int __cdecl mt76_incr(int val, int size)
{
  return (size - 1) & (val + 1);
}