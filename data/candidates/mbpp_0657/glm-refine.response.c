int __cdecl func0(int n)
{
  int i;
  int fact;

  fact = 1;
  for (i = 2; i <= n; ++i)
  {
    fact *= i;
    // Strip trailing zeros to prevent integer overflow
    while (fact % 10 == 0)
      fact /= 10;
  }
  // Extract the most significant digit
  while (fact >= 10)
    fact /= 10;
  
  return fact;
}