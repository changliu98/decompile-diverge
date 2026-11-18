void daxpy(uint n,double da,double *dx,double *dy)

{
  double *dy_local;
  double *dx_local;
  double da_local;
  uint n_local;
  
  if ((da != 0.0) || (NAN(da))) {
    n_local = n;
    if ((da != DAT_00102008) || (NAN(da) || NAN(DAT_00102008))) {
      do {
        n_local = n_local - 1;
        dy[n_local] = da * dx[n_local] + dy[n_local];
      } while (n_local != 0);
    }
    else {
      do {
        n_local = n_local - 1;
        dy[n_local] = dx[n_local] + dy[n_local];
      } while (n_local != 0);
    }
  }
  return;
}