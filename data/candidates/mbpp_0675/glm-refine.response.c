int __cdecl func0(int x, int y, int m, int n)
{
  int sum = x + y;

  if (sum < m || sum > n)
    return sum;
  else
    return 20;
}