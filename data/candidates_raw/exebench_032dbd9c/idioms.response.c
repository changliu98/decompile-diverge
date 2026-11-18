void dmatvec(double *a, double *b, int m, int n, double *c, int *p)
{
  int i; int j;
  double aj;
  *p = m + n;
  for (i = 0; i < 17; i++)
    c[i] = 0.;
  for (i = 0; i <= m; i++) {
    aj = a[i];
    for (j = 0; j <= n; j++)
      c[i + j] += aj * b[j];
  }
}