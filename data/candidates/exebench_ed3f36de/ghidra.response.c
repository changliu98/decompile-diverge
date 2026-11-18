void test_mean2(double *xymean,double *xy,int n)

{
  double ysum;
  double xsum;
  int i;
  int n_local;
  double *xy_local;
  double *xymean_local;
  
  xsum = 0.0;
  ysum = 0.0;
  for (i = 0; i < n * 2; i = i + 2) {
    xsum = xy[i] + xsum;
  }
  for (i = 0; i < n * 2; i = i + 2) {
    ysum = xy[i + 1] + ysum;
  }
  *xymean = xsum / (double)n;
  xymean[1] = ysum / (double)n;
  return;
}