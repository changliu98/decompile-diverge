int *func0(int n)
{
  int *result = (int *)malloc(sizeof(int) * n);
  int sum = 0;
  int prod = 1;

  for (int i = 1; i <= n; ++i)
  {
    sum += i;
    prod *= i;
    
    // For odd indices (1, 3, 5...), store the cumulative sum
    // For even indices (2, 4, 6...), store the cumulative product
    if (i % 2 != 0)
    {
      result[i - 1] = sum;
    }
    else
    {
      result[i - 1] = prod;
    }
  }
  
  return result;
}