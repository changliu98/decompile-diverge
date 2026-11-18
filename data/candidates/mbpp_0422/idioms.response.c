double func0(int n)
{
  int i;
  double sum = 0.0;
  for (i = 1; i <= n; i++)
  {
    sum += i * i * i;
  }
  return round(sum / n * 1000000.0) / 1000000.0;
}