bool _is_sorted(int *a, int n) {
  int i, c = 0;
  if (n == 0) return true;
  for (i = 1; i < n; i++) {
    if (a[i] < a[i - 1]) c++;
  }
  if (a[n - 1] > a[0]) c++;
  return c < 2;
}