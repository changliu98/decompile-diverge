unsigned long long func0(int n)
{
  unsigned long long fact = 1;
  unsigned long long bfact = 1;
  for (int i = 1; i <= n; i++)
    {
      fact *= i;
      bfact *= fact;
    }
  return bfact;
}