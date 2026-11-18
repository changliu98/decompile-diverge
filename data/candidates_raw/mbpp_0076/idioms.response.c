int nrect(int m, int n)
{
  int i; int j;
  int ret = 0;
  if (n < m)
  {
    i = m;
    m = n;
    n = i;
  }
  ret += m * (m + 1) * (n - m) / 2;
  ret += (m * (m * 2 + 1)) * m / 6;
  return (ret);
}