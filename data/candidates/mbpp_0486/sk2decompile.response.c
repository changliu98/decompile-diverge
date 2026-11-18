double _choose(int n, int k, double p) {
  int i, m;
  double c;
  m = k;
  if (k > n / 2) m = n - k;
  c = 1.0;
  for (i = 1; i <= m; i++) c = c * (n - m + i) / i;
  c = c * pow(p, k) * pow(1.0 - p, n - k);
  return c;
}