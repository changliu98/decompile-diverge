static int clip_wh(int *x, int *w, int min_x, int max_x) {
  int ret;
  if (*x < min_x) {
    ret = min_x - *x;
    *w += *x;
    *x = min_x;
    return ret;
  }
  if (*x + *w >= max_x) *w = max_x - *x;
  return 0;
}