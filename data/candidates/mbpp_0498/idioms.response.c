int func0(int a, int b)
{
  int i; int gcd = 1;
  if (a % b == 0)
    return b;
  for (i = b / 2; i > 0; i--)
  {
    if (a % i == 0 && b % i == 0)
    {
      gcd = i;
      break;
    }
  }
  return gcd;
}