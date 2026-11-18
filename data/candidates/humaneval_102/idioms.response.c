int func0(int n)
{
  if (n < 2)
    return (2);
  while (is_prime(n) == 0)
    n++;
  return (n);
}