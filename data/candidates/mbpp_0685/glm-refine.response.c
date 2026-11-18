int __cdecl func0(int n)
{
  // Allocate a boolean array (Variable Length Array) of size n + 1
  // v3 acts as the base pointer for this VLA
  char *is_prime = __builtin_alloca(n + 1);
  
  // Initialize all entries to 1 (true)
  for (int j = 0; j <= n; ++j)
    is_prime[j] = 1;

  // Sieve of Eratosthenes
  for (int p = 2; p * p <= n; ++p)
  {
    if (is_prime[p])
    {
      // Mark all multiples of p as 0 (false)
      for (int i = 2 * p; i <= n; i += p)
        is_prime[i] = 0;
    }
  }

  // Sum all numbers that are still marked as prime
  int sum = 0;
  for (int i = 2; i <= n; ++i)
  {
    if (is_prime[i])
      sum += i;
  }

  return sum;
}