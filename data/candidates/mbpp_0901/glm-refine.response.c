int __cdecl func0(int n)
{
  int na = n;
  if (n <= 2)
    return na;

  int i = 2 * na;
  int factor_count = 0;
  int factors[100];

  // Collect all numbers `x` in the range (n/2, n] 
  // These are the candidates that must divide the result `i`
  for (int number = na; number > 1; --number)
  {
    if (2 * number > na)
      factors[factor_count++] = number;
  }

  // Continuously increment `i` by `n` until it is evenly divisible 
  // by all collected factors. 
  while (true)
  {
    bool divisible = true;
    for (int j = 0; j < factor_count; ++j)
    {
      if (i % factors[j] != 0)
      {
        divisible = false;
        break;
      }
    }
    
    if (divisible)
      return i;
      
    i += na;
  }
}