void rgb2hsv(int r, int g, int b, int *h, int *s, int *v)
{
  int max; int min;
  if ( r > g )
    max = r;
  else
    max = g;
  if ( b > max )
    max = b;
  if ( r < g )
    min = r;
  else
    min = g;
  if ( b < min )
    min = b;
  if (max == 0) {
    *h = *s = *v = 0;
  } else {
    if (max == min)
      *h = 0;
    else if (max == r && g >= b)
      *h = (int)(1.0 * (g - b) * (1.0 * 600 / (max - min)));
    else if (max == r && g < b)
      *h = (int)(1.0 * (g - b) * (1.0 * 600 / (max - min)) + 1.0 * 360 * 10);
    else if (max == g)
      *h = (int)(1.0 * (b - r) * (1.0 * 600 / (max - min)) + 1.0 * 120 * 10);
    else
      *h = (int)(1.0 * (r - g) * (1.0 * 600 / (max - min)) + 1.0 * 240 * 10);
    while (*h < 0)
      *h += 3600;
    while (*h >= 3600)
      *h -= 3600;
    *s = (int)(1.0 * (max - min) * (1.0 * 255 / max));
    *v = max;
  }
}