void _sub(int *a, int *b, int *c, int n) {
  int i;
  for (i = 0; i < n; i++) {
    c[i] = abs(a[i] - b[i]);
  }
}