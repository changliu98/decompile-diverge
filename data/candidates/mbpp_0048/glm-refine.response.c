int __cdecl func0(int n)
{
  int res = 0;
  int bit_pos = 0;

  for (int temp = n; temp > 0; temp >>= 1, ++bit_pos) {
    if ((bit_pos & 1) == 0)
      res |= 1 << bit_pos;
  }
  return res | n;
}