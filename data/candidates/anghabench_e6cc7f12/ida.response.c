int __cdecl aligned(int val)
{
  return (val + 63) >> 6 << 6;
}