int __cdecl fit_line(double *x, double *y, int count, double *a, double *b)
{
  int i; // [rsp+0h] [rbp-5Ch]
  double denom; // [rsp+4h] [rbp-58h]
  double sumx2; // [rsp+Ch] [rbp-50h]
  double sumxy; // [rsp+14h] [rbp-48h]
  double sumy; // [rsp+1Ch] [rbp-40h]
  double sumx; // [rsp+24h] [rbp-38h]

  sumx2 = 0.0;
  sumxy = 0.0;
  sumy = 0.0;
  sumx = 0.0;
  for ( i = 0; i < count; ++i )
  {
    sumx = x[i] + sumx;
    sumx2 = x[i] * x[i] + sumx2;
    sumy = y[i] + sumy;
    sumxy = x[i] * y[i] + sumxy;
  }
  denom = (double)count * sumx2 - sumx * sumx;
  if ( denom == 0.0 )
    return -1;
  *a = (sumy * sumx2 - sumx * sumxy) / denom;
  *b = ((double)count * sumxy - sumx * sumy) / denom;
  return 0;
}