void ZVdotC11(int n, double *y, double *x, double *sum)
{
  int i; int j; int k;
  double sum_xx; double sum_xy; double sum_yy;
  sum_xx = sum_xy = sum_yy = 0.;
  for (i = j = k = 0, iloc = 1; i < n; i++, j += 2, k += 2) {
    sum_xx += (y[j] * x[j]) + (y[k] * x[k]);
    sum_xy += (y[j] * x[k]) - (y[k] * x[j]);
  }
  sum[0] = sum_xx;
  sum[1] = sum_xy;
  return;
}