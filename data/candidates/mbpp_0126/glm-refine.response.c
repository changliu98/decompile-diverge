int __cdecl func0(int a, int b)
{
  int min_val = (a < b) ? a : b;
  int sum = 0;

  for (int i = 1; i < min_val; ++i)
  {
    if (a % i == 0 && b % i == 0)
      sum += i;
  }
  
  return sum;
}