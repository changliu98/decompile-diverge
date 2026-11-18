int *__cdecl func0(int n, int *count)
{
  int *primes; 
  int current; 
  int is_prime; 
  int j; 
  int prime; 

  primes = (int *)malloc(4LL * n);
  *count = 0;
  
  for (current = 2; current < n; ++current)
  {
    is_prime = 1;
    for (j = 0; j < *count; ++j)
    {
      prime = primes[j];
      // If the square of the prime is greater than the current number, 
      // no larger prime can be a factor.
      if (prime * prime > current)
        break;
      // If 'current' is divisible by a known prime, it's not a prime.
      if (!(current % prime))
      {
        is_prime = 0;
        break;
      }
    }
    if (is_prime)
      primes[(*count)++] = current;
  }
  
  return primes;
}