int func0(int* a, int n) {
  int r = 0;
  for (int i = 0; i < n; i++) {
    r *= 10;
    r += a[i];
  }
  return r;
}