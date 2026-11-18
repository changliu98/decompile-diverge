void rgb2hsv(double r, double g, double b, double *h, double *s, double *v) {
  double hue = 0.0;
  double sat = 0.0;
  double min = (((r) < (g)) ? (r) : (g));
  min = (((min) < (b)) ? (min) : (b));
  double max = (((r) > (g)) ? (r) : (g));
  max = (((max) > (b)) ? (max) : (b));
  if (max > 0.0) {
    sat = (max - min) / max;
  }
  if (sat > 0.0) {
    double rc = (max - r) / (max - min);
    double gc = (max - g) / (max - min);
    double bc = (max - b) / (max - min);
    if (r == max) {
      hue = bc - gc;
    } else if (g == max) {
      hue = 2.0 + rc - bc;
    } else if (b == max) {
      hue = 4.0 + gc - rc;
    }
    hue *= 60.0;
    if (hue < 0.0) {
      hue += 360.0;
    }
  }
  *h = hue / 360.0;
  *v = max;
  *s = sat;
}