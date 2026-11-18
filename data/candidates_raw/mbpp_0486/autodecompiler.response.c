double binomial_tail(int n, int k, double p)
{
  int i, tail;

  tail = k;
  if (k > n/2) tail = n-k;

  double cdf = 1.0;
  for (i=1; i<=tail; i++) {
    cdf *= (n-k+i);
    cdf /= i;
  }
  cdf *= pow(p, (double)k) * pow(1-p, (double)(n-k));

  return(cdf);
}