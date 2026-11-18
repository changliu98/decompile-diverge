void tigrFill(Tigr *bmp,int x,int y,int w,int h,TPixel color)

{
  int iVar1;
  int i;
  int dt;
  TPixel *td;
  int h_local;
  int w_local;
  int y_local;
  int x_local;
  Tigr *bmp_local;
  TPixel color_local;
  
  w_local = w;
  x_local = x;
  if (x < 0) {
    w_local = x + w;
    x_local = 0;
  }
  h_local = h;
  y_local = y;
  if (y < 0) {
    h_local = y + h;
    y_local = 0;
  }
  if (bmp->w < x_local + w_local) {
    w_local = bmp->w - x_local;
  }
  if (bmp->h < y_local + h_local) {
    h_local = bmp->h - y_local;
  }
  if ((0 < w_local) && (0 < h_local)) {
    td = bmp->pix + (y_local * bmp->w + x_local);
    iVar1 = bmp->w;
    do {
      for (i = 0; i < w_local; i = i + 1) {
        td[i] = color;
      }
      td = td + iVar1;
      h_local = h_local + -1;
    } while (h_local != 0);
  }
  return;
}