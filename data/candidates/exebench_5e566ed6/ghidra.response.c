int fit_line(double *x,double *y,int count,double *a,double *b)

{
  double dVar1;
  int i;
  double denom;
  double sumx2;
  double sumxy;
  double sumy;
  double sumx;
  double *b_local;
  double *a_local;
  int count_local;
  double *y_local;
  double *x_local;
  int local_c;
  
  sumx2 = 0.0;
  sumxy = 0.0;
  sumy = 0.0;
  sumx = 0.0;
  for (i = 0; i < count; i = i + 1) {
    sumx = x[i] + sumx;
    sumx2 = x[i] * x[i] + sumx2;
    sumy = y[i] + sumy;
    sumxy = x[i] * y[i] + sumxy;
  }
  dVar1 = (double)count * sumx2 + -(sumx * sumx);
  if ((dVar1 != 0.0) || (NAN(dVar1))) {
    *a = (sumy * sumx2 + -(sumx * sumxy)) / dVar1;
    *b = ((double)count * sumxy + -(sumx * sumy)) / dVar1;
    local_c = 0;
  }
  else {
    local_c = -1;
  }
  return local_c;
}