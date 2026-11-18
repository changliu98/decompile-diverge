void _minmax(int *a, int n, int *res) {
  int i, min = 0, max = 0;
  for (i = 0; i < n; i++) {
    if (a[i] < 0 && (!min || a[i] > min)) min = a[i];
    if (a[i] > 0 && (!max || a[i] < max)) max = a[i];
  }
  res[0] = min;
  res[1] = max;
}