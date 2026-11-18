int func0(int n)
{
  int i;
  int result = 0;

  for (i = 2; i <= sqrt(n); i++)
    if (n % i == 0)
      result = 1;

  return result;
}