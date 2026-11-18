int func0(int n)
{
  int i = 0;
  for (i = 0; i * i * i <= abs(n); i++)
    if (i * i * i == abs(n))
      return 1;
  return 0;
}