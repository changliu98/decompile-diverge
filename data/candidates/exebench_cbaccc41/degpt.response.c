int clip(double *px,double *py,double *pz,double xmin,double xmax,double ymin,double ymax,
        double zmin,double zmax)

{
  double dVar1;
  int iClip;
  double zmax_local;
  double zmin_local;
  double ymax_local;
  double ymin_local;
  double xmax_local;
  double xmin_local;
  double *pz_local;
  double *py_local;
  double *px_local;
  
  if (xmin <= *px) {
    dVar1 = *px;
    if (xmax < dVar1) {
      *px = xmax;
    }
    iClip = (int)(xmax < dVar1);
  }
  else {
    *px = xmin;
    iClip = 1;
  }
  if (ymin <= *py) {
    if (ymax < *py) {
      *py = ymax;
      iClip = 1;
    }
  }
  else {
    *py = ymin;
    iClip = 1;
  }
  if (zmin <= *pz) {
    if (zmax < *pz) {
      *pz = zmax;
      iClip = 1;
    }
  }
  else {
    *pz = zmin;
    iClip = 1;
  }
  return iClip;
}