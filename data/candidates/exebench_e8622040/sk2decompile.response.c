int doit(int *p, int x) {
  if (*p > x) {
    *p = x;
    return 1;
  }
  return 0;
}