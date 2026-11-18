int ctr_intersect(double z0,double z1,double zc,double *f)

{
  bool bVar1;
  double *f_local;
  double zc_local;
  double z1_local;
  double z0_local;
  uint local_c;
  
  bVar1 = (z0 - zc) * (z1 - zc) < 0.0;
  if (bVar1) {
    *f = (zc - z0) / (z1 - z0);
  }
  local_c = (uint)bVar1;
  return local_c;
}