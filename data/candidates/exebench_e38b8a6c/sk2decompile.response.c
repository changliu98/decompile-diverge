static int clip_img(int x1, int y1, int x2, int y2, int *x, int *y, int *w,
                    int *h, int *u, int *v, int u_stride, int v_stride) {
  if (*x < x1) {
    *w -= x1 - *x;
    *u += (x1 - *x) * u_stride;
    *x = x1;
  }
  if (*w > x2 - *x + 1) *w = x2 - *x + 1;
  if (*y < y1) {
    *h -= y1 - *y;
    *v += (y1 - *y) * v_stride;
    *y = y1;
  }
  if (*h > y2 - *y + 1) *h = y2 - *y + 1;
  return *w >= 0 && *h >= 0;
}