double func0(int n)
{
  double nCr = 1.0;
  double sum = 1.0;
  int i;
  for (i = 1; i <= n; i++)
  {
    nCr = nCr * (n + 1 - i) / i;
    sum += nCr * nCr;
  }
  return sum;
}