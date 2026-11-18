void project(int n, double *y, int *zp)
{
  int i;
  for(i=0; i<n; i++)
    if(zp[i])
      y[i] = 0.0;
}