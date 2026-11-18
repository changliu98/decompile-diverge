int __cdecl func0(int n, int x, int y)
{
  int i;
  int is_prime;

  // Assume n is prime if it's 2 or greater
  is_prime = (n >= 2);

  // Check for factors up to the square root of n
  for (i = 2; i * i <= n; ++i)
  {
    if (n % i == 0)
      is_prime = 0;
  }

  // Return y if n is not prime, otherwise return x
  if (!is_prime)
    return y;
    
  return x;
}