void rgb2hsv(int r, int g, int b, int *h, int *s, int *v)
{
   int max, min, delta;

   max = (((r) > (((g) > (b) ? (g) : (b)))) ? (r) : (((g) > (b) ? (g) : (b))));
   min = (((r) < (((g) < (b) ? (g) : (b)))) ? (r) : (((g) < (b) ? (g) : (b))));
   delta = max - min;

   if (max != 0)
      *s = delta / (float) max;
   else {
      *s = 0;
      *h = 0;
      *v = 0;
      return;
   }

   if (max == r && g >= b)
      *h = (g - b) * 600 / delta;
   else if (max == r && g < b)
      *h = (g - b) * 600 / delta + 6000;
   else if (max == g && b >= r)
      *h = (b - r) * 600 / delta + 2000;
   else
      *h = (r - g) * 600 / delta + 4000;

   while (*h < 0)
      *h += 6000;

   while (*h >= 6000)
      *h -= 6000;

   *v = max * 255 / 255;
}