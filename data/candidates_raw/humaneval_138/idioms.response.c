int is_prime(int n)
{
  int i;
  int isprime = 1;
  if (n < 2)
    return 0;
  for (i = 2; i < n; i++)
    if (n % i == 0)
      isprime = 0;
  return isprime;
}