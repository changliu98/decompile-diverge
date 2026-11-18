int _get_range(int x1, int y1, int x2, int y2, int *x1_out, int *y1_out) {
  *x1_out = (x1 == x2) ? -1 : (x1 < x2) ? x1 : x2;
  *y1_out = (y1 == y2) ? -1 : (y1 > y2) ? y1 : y2;
  return 0;
}