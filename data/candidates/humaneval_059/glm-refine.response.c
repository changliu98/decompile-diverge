int __cdecl func0(int n)
{
  for (int i = 2; i * i <= n; ++i)
  {
    // Repeatedly divide n by i as long as i is a proper divisor of n
    while (n % i == 0 && n > i)
    {
      n /= i;
    }
  }
  return n;
}