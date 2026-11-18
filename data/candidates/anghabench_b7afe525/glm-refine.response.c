int __cdecl mt76_incr(int index, int ring_size)
{
  return (ring_size - 1) & (index + 1);
}