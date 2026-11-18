void rgb_2_hls(int r, int g, int b, int *h, int *l, int *s)
{
 int max, min;

 max = r;
 if (g > max)
  max = g;
 if (b > max)
  max = b;

 min = r;
 if (g < min)
  min = g;
 if (b < min)
  min = b;

 *l = (max + min) / 20;

 if (max == min) {
  *h = 0;
  *s = 0;
 } else {
  int tmp;

  if (*l < 50)
   *s = 100 * (max - min) / (max + min);
  else
   *s = 100 * (max - min) / (2000 - max - min);

  if (max == r)
   tmp = (g - b) * 60 / (max - min) + 120;
  else if (max == g)
   tmp = (b - r) * 60 / (max - min) + 240;
  else
   tmp = (r - g) * 60 / (max - min) + 360;

  *h = tmp % 360;
 }
}