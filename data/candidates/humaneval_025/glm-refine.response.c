int *func0(int n, int *size)
{
  int i;
  int *out = (int *)malloc(0x100uLL);
  
  *size = 0;
  
  // Check for prime factors up to the square root of n
  for (i = 2; i * i <= n; ++i)
  {
    while (n % i == 0)
    {
      n /= i;
      out[(*size)++] = i;
    }
  }
  
  // If n is still greater than 1, then it is a prime factor
  if (n > 1)
  {
    out[(*size)++] = n;
  }
  
  return out;
}