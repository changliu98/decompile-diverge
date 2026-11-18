int fit_line(double *x, double *y, int count, double *a, double *b)
{
 double sumx2, sumxy, sumy, sumx;
 double denom;
 int i;

 sumx2 = 0.0;
 sumxy = 0.0;
 sumy = 0.0;
 sumx = 0.0;
 for (i = 0; i < count; i++)
 {
  sumx += x[i];
  sumx2 += x[i] * x[i];
  sumy += y[i];
  sumxy += x[i] * y[i];
 }

 denom = count * sumx2 - sumx * sumx;
 if (denom == 0.0)
  return -1;

 *a = (sumy * sumx2 - sumx * sumxy) / denom;
 *b = (count * sumxy - sumx * sumy) / denom;

 return 0;
}