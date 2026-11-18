int linear_fit(double *x, double *y, int count, double *a, double *b)
{
  double sumx = 0.0;
  double sumx2 = 0.0;
  double sumxy = 0.0;
  double sumy = 0.0;
  int i;
  for (i = 0; i < count; i++)
  {
    sumx += x[i];
    sumx2 += x[i]*x[i];
    sumy += y[i];
    sumxy += x[i]*y[i];
  }
  double denom = (double)count * sumx2 - sumx * sumx;
  if (denom == 0.0)
    return -1;
  *a = (sumy * sumx2 - sumx * sumxy) / denom;
  *b = (sumxy * (double)count - sumx * sumy) / denom;
  return 0;
}