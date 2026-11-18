int func0(int x, int y) {
  int q = x / y;
  int r = x % y;
  int p = q * y;
  if (r > p + y - x) {
    return p + y;
  } else {
    return p;
  }
}