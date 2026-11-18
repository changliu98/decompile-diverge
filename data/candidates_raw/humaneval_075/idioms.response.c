int is_prime_power(int n)
{
  int i; int p; int c;
  for (i = p = c = n; i < i*i && p != 1; i++)
    while (p % i == 0)
      {
        p = p / i;
        c++;
      }
  if (p > 1)
    c++;
  return c == 3;
}