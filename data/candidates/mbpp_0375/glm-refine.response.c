int __cdecl func0(int n, int m)
{
  int q = n / m;
  int r = n % m;

  if (r <= m - r)
    return q * m;
  else
    return q * m + m;
}