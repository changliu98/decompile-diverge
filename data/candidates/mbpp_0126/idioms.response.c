int func0(int a, int b)
{
  int sum = 0;
  int i = 1;
  int max = a < b ? a : b;
  for (i = 1; i < max; i++)
  {
    if (a % i == 0 && b % i == 0)
    {
      sum += i;
    }
  }
  return sum;
}