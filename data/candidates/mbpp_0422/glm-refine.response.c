double __cdecl func0(int n)
{
  double sum = 0.0;
  for (int i = 1; i <= n; ++i)
    sum += (double)(i * i * i);
  return round(sum / (double)n * 1000000.0) / 1000000.0;
}