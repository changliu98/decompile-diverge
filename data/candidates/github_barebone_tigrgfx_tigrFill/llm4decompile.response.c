void tigrFill(Tigr *bmp, int x, int y, int w, int h, TPixel color)
{
  TPixel *p;
  int i,j;

  if (x < 0) {
    w += x;
    x = 0;
  }
  if (y < 0) {
    h += y;
    y = 0;
  }
  if (x + w > bmp->w) {
    w = bmp->w - x;
  }
  if (y + h > bmp->h) {
    h = bmp->h - y;
  }
  if (w <= 0 || h <= 0) {
    return;
  }

  p = bmp->pix + (y * bmp->w + x);
  for (j = h; j > 0; j--) {
    for (i = 0; i < w; i++) {
      p[i] = color;
    }
    p += bmp->w;
  }
}