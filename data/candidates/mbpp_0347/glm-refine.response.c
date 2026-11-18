int __cdecl func0(int m, int n)
{
  int max_val = m < n ? n : m;
  int min_val = m < n ? m : n;

  return (3 * max_val - min_val + 1) * (min_val + 1) * min_val / 6;
}