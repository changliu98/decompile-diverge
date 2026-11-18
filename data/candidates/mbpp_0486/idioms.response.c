double func0(int n, int r, double p)
{
  int i; int j;
  double ret = 1;
  if ( r > n / 2 )
    r = n - r;
  for ( i = 1; i <= r; i++ )
    ret *= (double)(i + n - r) / (double)i;
  ret *= pow(p, r);
  ret *= pow(1 - p, n - r);
  return ret;
}