void rgb2cmyk(double r,double g,double b,double *c,double *m,double *y,double *k)

{
  undefined8 local_50;
  undefined8 local_48;
  double *k_local;
  double *y_local;
  double *m_local;
  double *c_local;
  double b_local;
  double g_local;
  double r_local;
  
  *c = DAT_00102010 - r;
  *m = DAT_00102010 - g;
  *y = DAT_00102010 - b;
  if (*m <= *c) {
    local_48 = *m;
  }
  else {
    local_48 = *c;
  }
  *k = local_48;
  if (*k <= *y) {
    local_50 = *k;
  }
  else {
    local_50 = *y;
  }
  *k = local_50;
  *c = *c - *k;
  *m = *m - *k;
  *y = *y - *k;
  return;
}