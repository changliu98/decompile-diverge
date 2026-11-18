int *func0(int *a, int n, int x, int *m) {
  int i, j, k;
  int *b;
  *m = (n > 0) ? 2 * n - 1 : 0;
  b = (int *)malloc(sizeof(int) * (*m));
  if (n > 0) b[0] = a[0];
  for (i = 1, j = 1; i < n; i++) {
    b[j++] = x;
    b[j++] = a[i];
  }
  return b;
}