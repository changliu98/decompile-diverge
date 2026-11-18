int __cdecl func0(int n)
{
  int sum = 0;
  for (int i = 1; i <= n; ++i)
    sum += 16 * (i * i * i * i);
  return sum;
}