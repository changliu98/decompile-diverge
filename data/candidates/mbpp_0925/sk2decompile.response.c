int func0(int* a, int n) {
  int p = 1;
  for (int i = 0; i < n; i++) {
    p *= a[i];
  }
  return p;
}