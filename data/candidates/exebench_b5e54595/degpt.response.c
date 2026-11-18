int zuchk_(double *yr,double *yi,int *nz,double *ascle,double *tol)

{
  undefined8 local_78;
  undefined8 local_70;
  undefined8 local_68;
  undefined8 local_60;
  double wr;
  double st;
  double ss;
  double wi;
  double *tol_local;
  double *ascle_local;
  int *nz_local;
  double *yi_local;
  double *yr_local;
  
  *nz = 0;
  if (*yr < 0.0) {
    local_60 = -*yr;
  }
  else {
    local_60 = *yr;
  }
  if (*yi < 0.0) {
    local_68 = -*yi;
  }
  else {
    local_68 = *yi;
  }
  if (local_68 < local_60) {
    local_70 = local_68;
  }
  else {
    local_70 = local_60;
  }
  if (local_70 < *ascle || local_70 == *ascle) {
    if (local_60 < local_68) {
      local_78 = local_68;
    }
    else {
      local_78 = local_60;
    }
    if (local_78 < local_70 / *tol) {
      *nz = 1;
    }
  }
  return 0;
}