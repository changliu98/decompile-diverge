void rgb_to_cmy(double r, double g, double b, double *c, double *m, double *y, double *k)
{
 double min_rg, min_cy;

 *c = 1.0 - r;
 *m = 1.0 - g;
 *y = 1.0 - b;

 if (*c < *m) {
  min_rg = *c;
 } else {
  min_rg = *m;
 }

 *k = min_rg;
 if (*y < *k) {
  min_cy = *y;
 } else {
  min_cy = *k;
 }

 *c -= *k;
 *m -= *k;
 *y -= *k;
}