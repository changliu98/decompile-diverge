void tigrFill(Tigr *img, int x, int y, int w, int h, tigrRGB color) {
  unsigned char *pix;
  int i, j, row;
  if (x < 0) {
    w += x;
    x = 0;
  }
  if (y < 0) {
    h += y;
    y = 0;
  }
  if (x + w > img->w) w = img->w - x;
  if (y + h > img->h) h = img->h - y;
  if (w <= 0 || h <= 0) return;
  pix = img->pixels + y * img->w + x;
  row = img->w;
  do {
    for (i = 0; i < w; i++) {
      *(tigrRGB *)pix = color;
      pix += 4;
    }
    pix += row;
  } while (--h);
}