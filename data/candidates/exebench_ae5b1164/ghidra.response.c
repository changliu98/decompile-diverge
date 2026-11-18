int ctr_intersect(double z0,double z1,double zc,double *f)

{
  double *f_local;
  double zc_local;
  double z1_local;
  double z0_local;
  int local_c;
  
  if (((z0 < zc == z1 < zc) || ((z0 == zc && (!NAN(z0) && !NAN(zc))))) ||
     ((z1 == zc && (!NAN(z1) && !NAN(zc))))) {
    local_c = 0;
  }
  else {
    *f = (zc - z0) / (z1 - z0);
    local_c = 1;
  }
  return local_c;
}