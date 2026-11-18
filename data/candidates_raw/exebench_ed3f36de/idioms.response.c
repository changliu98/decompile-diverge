void getxymean(double *xymean, double *xy, int n)
{
  int i;
  double xsum = 0.; double ysum = 0.;
  for (i = 0; i < 2 * n; i += 2)
    xsum += xy[i];
  for (i = 0; i < 2 * n; i += 2)
    ysum += xy[i + 1];
  xymean[0] = xsum / n;
  xymean[1] = ysum / n;
}