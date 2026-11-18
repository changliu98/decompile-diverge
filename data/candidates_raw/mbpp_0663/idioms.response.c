int get_next_in_group(int n, int x, int y)
{
  int i;
  int next = -0x7fffffff - 1;
  for (i = 0; i <= n; i++)
    if (i % x == y && i > next)
      next = i;
  if (next < 0 || next > n)
    return -1;
  return next;
}