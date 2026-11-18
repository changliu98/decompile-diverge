void rgb2hsv(double r, double g, double b, double *h, double *s, double *v)
{
 double ht = 0.0;
 double st = 0.0;
 double vt = 0.0;
 double rgbmax = r;
 double rgbmin = r;

 if (g > rgbmax) rgbmax = g;
 if (b > rgbmax) rgbmax = b;
 if (g < rgbmin) rgbmin = g;
 if (b < rgbmin) rgbmin = b;

 vt = rgbmax;
 st = (rgbmax - rgbmin) / rgbmax;
 if (st > 0.0) {
  double rd = (rgbmax - r) / (rgbmax - rgbmin);
  double gd = (rgbmax - g) / (rgbmax - rgbmin);
  double bd = (rgbmax - b) / (rgbmax - rgbmin);

  if (r == rgbmax) ht = bd - gd;
  else if (g == rgbmax) ht = rd - bd + 2.0;
  else if (b == rgbmax) ht = gd - rd + 4.0;
  ht *= 60.0;
  if (ht < 0.0) ht += 360.0;
 }
 *h = ht / 360.0;
 *v = vt;
 *s = st;
}