void rgb2hsv(int r, int g, int b, int *h, int *s, int *v)
{
 int max, min;

 max = r > g ? r : g;
 max = max > b ? max : b;

 min = r < g ? r : g;
 min = min < b ? min : b;

 if (max == 0) {
  *v = 0;
  *h = 0;
  *s = 0;
  return;
 }

 if (max == min) {
  *h = 0;
 } else if (max == r && g >= b) {
  *h = 60 * (g - b) / (max - min);
 } else if (max == r && g < b) {
  *h = 60 * (g - b) / (max - min) + 360;
 } else if (max == g) {
  *h = 60 * (b - r) / (max - min) + 120;
 } else {
  *h = 60 * (r - g) / (max - min) + 240;
 }

 while (*h < 0)
  *h += 3600;

 while (*h >= 3600)
  *h -= 3600;

 *s = 255 * (max - min) / max;
 *v = max;
}