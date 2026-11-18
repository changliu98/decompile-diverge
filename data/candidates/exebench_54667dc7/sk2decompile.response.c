void drv_generic_graphic_window(int x, int w, int max_x, int *x1, int *w1) {
  int x2 = x;
  int x3 = x + w;
  *x1 = 0;
  *w1 = 0;
  if (x2 <= max_x && x3 >= 0 && w >= 1) {
    if (x2 < 0) x2 = 0;
    if (x3 > max_x) x3 = max_x;
    *x1 = x2;
    *w1 = x3 - x2;
  }
}