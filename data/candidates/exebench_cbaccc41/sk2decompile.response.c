int clip(double *x, double *y, double *z, double xmin, double xmax, double ymin,
         double ymax, double zmin, double zmax) {
  int ret = 0;
  if (*x < xmin) {
    *x = xmin;
    ret = 1;
  } else if (*x > xmax) {
    *x = xmax;
    ret = 1;
  }
  if (*y < ymin) {
    *y = ymin;
    ret = 1;
  } else if (*y > ymax) {
    *y = ymax;
    ret = 1;
  }
  if (*z < zmin) {
    *z = zmin;
    ret = 1;
  } else if (*z > zmax) {
    *z = zmax;
    ret = 1;
  }
  return ret;
}