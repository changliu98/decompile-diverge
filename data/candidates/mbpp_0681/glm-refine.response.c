int __cdecl func0(int n)
{
  // If n is even, 2 is its smallest prime factor
  if (n % 2 == 0)
    return 2;

  // Check odd factors from 3 up to sqrt(n)
  for (int i = 3; i * i <= n; i += 2)
  {
    // If i divides n evenly, it is the smallest prime factor
    if (n % i == 0)
      return i;
  }

  // If no factors were found, n is prime
  return n;
}