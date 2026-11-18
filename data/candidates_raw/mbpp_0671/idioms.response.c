int next_power_of_two(int n)
{
  if (n == 0)
    return 1;
  int mask = n + 1 & ~n;
  if (mask == 0)
    return n;
  int shift = (int)(log2(mask)) + 1;
  return n | (1 << (shift - 1));
}