void RGBtoHSV(float r, float g, float b, float *h, float *s, float *v) {
  float min, max, delta, rdelta, gdelta;
  min = (r < g) ? r : g;
  min = (min < b) ? min : b;
  max = (r > g) ? r : g;
  max = (max > b) ? max : b;
  *v = max;
  gdelta = max - min;
  if (max == 0) {
    *s = 0;
    *h = -1;
  } else {
    *s = gdelta / max;
    if (r == max)
      *h = (g - b) / gdelta;
    else if (g == max)
      *h = 2 + (b - r) / gdelta;
    else
      *h = 4 + (r - g) / gdelta;
    *h *= 60;
    if (*h < 0) *h += 360;
  }
}