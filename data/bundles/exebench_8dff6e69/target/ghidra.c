void dxpy1(int n,double *dx,double *dy)

{
  int i;
  double *dy_local;
  double *dx_local;
  int n_local;
  
  for (i = 0; i < n; i = i + 1) {
    dy[i] = dx[i] + dy[i];
  }
  return;
}