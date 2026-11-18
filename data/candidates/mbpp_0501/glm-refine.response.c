int __cdecl func0(int x, int y)
{
  int n = ngcd(x, y);
  int result = 0;
  int z = (int)sqrt((double)n);

  for (int i = 1; i <= z; ++i)
  {
    if (n % i == 0)
    {
      result += 2;
      if (i == n / i)
        --result;
    }
  }
  
  return result;
}