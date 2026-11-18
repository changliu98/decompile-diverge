void rgb2hsl(int r, int g, int b, int *h, int *l, int *s)
{
  int min; int max; int t;
  if (g < r)
    min = r;
  else
    min = g;
  if (min > b)
    min = b;
  if (g > r)
    max = r;
  else
    max = g;
  if (max < b)
    max = b;
  *l = (min + max) * 10 / 200;
  if (min == max) {
    *h = 0;
    *s = 0;
  }
  else {
    if (*l < 50)
      *s = (max - min) * 100 / (min + max);
    else
      *s = (max - min) * 100 / (2 * 100 - max - min);
    if (r == max)
      *h = (g - b) * 10 * 6 / (max - min) + 120;
    else if (g == max)
      *h = (b - r) * 10 * 6 / (max - min) + 240;
    else
      *h = (r - g) * 10 * 6 / (max - min) + 360;
    *h = *h % 360;
  }
}