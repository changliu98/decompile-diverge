void rgb2hsv(int r, int g, int b, int *h, int *s, int *v) {
  int max, min, mid;
  mid = (r > g) ? r : g;
  if (b > mid) mid = b;
  min = (r < g) ? r : g;
  if (b < min) min = b;
  if (mid == 0) {
    *v = 0;
    *h = 0;
    *s = 0;
    return;
  }
  if (mid == min)
    *h = 0;
  else if (r == mid && g >= b)
    *h = 600 * (g - b) / (mid - min);
  else if (r == mid && g < b)
    *h = 60 * (g - b) / (mid - min) + 3600;
  else if (g == mid)
    *h = 60 * (b - r) / (mid - min) + 1200;
  else
    *h = 60 * (r - g) / (mid - min) + 2400;
  while (*h < 0) *h += 3600;
  while (*h >= 3600) *h -= 3600;
  *s = 255 * (mid - min) / mid;
  *v = mid;
}