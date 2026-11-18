int
fit_line(double *x,
       double *y,
       int n,
       double *ret_a,
       double *ret_b)
{
  double sumx = 0.0;
  double sumx2 = 0.0;
  double sumxy = 0.0;
  double sumy = 0.0;
  double denom;
  int i;
  int ret;

  for (i = 0; i < n; i++)
    {
      sumx += x[i];
      sumx2 += x[i] * x[i];
      sumy += y[i];
      sumxy += x[i] * y[i];
    }

  denom = (double) n * sumx2 + (-(sumx * sumx));

  if (denom == 0.0)
    ret = -1;
  else
    {
      *ret_a = ((sumy * sumx2) + (-sumx * sumxy)) / denom;
      *ret_b = ((n * sumxy) + (-sumx * sumy)) / denom;
      ret = 0;
    }
  return ret;
}