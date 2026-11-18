int func0(int *a, int n) {
  int i, p = 1;
  for (i = 0; i < n; i++) {
    p *= a[i];
  }
  return p;
}