int next(int *a, int n) {
  int i;
  for (i = 0; i < n && a[i]; i++) a[i] = 0;
  if (i >= n) return 0;
  a[i] = 1;
  return 1;
}