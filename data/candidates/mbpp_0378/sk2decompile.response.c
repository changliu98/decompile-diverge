void _rotate_left(int *a, int n, int *b) {
  int i;
  b[0] = a[n - 1];
  for (i = 1; i < n; i++) {
    b[i] = a[i - 1];
  }
}