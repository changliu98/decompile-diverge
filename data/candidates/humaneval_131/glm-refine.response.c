int __cdecl func0(int n)
{
  int has_odd = 0;
  int product = 1;

  while (n > 0)
  {
    int digit = n % 10;
    
    if (digit % 2 == 1)
    {
      has_odd = 1;
      product *= digit;
    }
    
    n /= 10;
  }

  if (has_odd)
    return product;
  else
    return 0;
}