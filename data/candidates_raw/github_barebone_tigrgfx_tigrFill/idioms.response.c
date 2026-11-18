void TigrFillRect(struct _Tigr *tigr, int x, int y, int w, int h, struct _TPixel color)
{
  int i; int j; int k;
  struct _TPixel *pix;
  int dx; int dy; int dw; int dh;
  dx = x;
  dy = y;
  dw = w;
  dh = h;
  if (dx < 0) {
    dw += dx;
    dx = 0;
  }
  if (dy < 0) {
    dh += dy;
    dy = 0;
  }
  if (dx + dw > tigr->w)
    dw = tigr->w - dx;
  if (dy + dh > tigr->h)
    dh = tigr->h - dy;
  if (dw > 0 && dh > 0) {
    pix = &tigr->pix[dx + dy * tigr->w];
    k = tigr->w;
    do {
      for (i = 0; i < dw; i++)
        pix[i] = color;
      pix += k;
      dh--;
    } while (dh);
  }
}