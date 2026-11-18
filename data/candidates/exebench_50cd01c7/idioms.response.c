void splini(double *xa, double *ya, double *y2a, int n, double x, double *y)
{
  int i; int j;
  double s; double del; double t; double u; double v; double w; double yval;
  yval = 0.;
  for (i = j = 0; i < n; i++) {
    if (x > xa[j])
      if (i < n - 1 && x > xa[i])
        break;
    del = xa[i] - xa[j];
    s = (xa[i] - x)/del;
    t = (x - xa[j])/del;
    yval += (ya[j]*((1 - s*s)/2) + ya[i]*((t*t)/2)
            + (y2a[j]*((-(s*s)*(s*s) - 1)/4 + s*s/2)*del*del
            + y2a[i]*((t*t)*(t*t)/4 - t*t/2)*del*del)/6.)*del;
  }
  *y = yval;
}