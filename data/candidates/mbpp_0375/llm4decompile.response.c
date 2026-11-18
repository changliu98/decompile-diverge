int func0(int n, int m)
{
 int r = n % m;
 int q = n / m;
 int p = q * m;
 int d1 = n - p;
 int d2 = p + m - n;

 if (d1 > d2)
  return p + m;
 else
  return p;
}