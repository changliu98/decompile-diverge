int func0(int l1, int r1, int l2, int r2, int *x, int *y) {
  *x = (l1 != l2) ? ((l1 < l2) ? l1 : l2) : -1;
  *y = (r1 != r2) ? ((r1 > r2) ? r1 : r2) : -1;
  return 0;
}