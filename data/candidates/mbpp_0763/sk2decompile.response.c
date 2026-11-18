int func0(int *a, int n) {
  int i, j, t, min;
  for (j = 0; j < n - 1; j++) {
    for (i = 0; i < n - j - 1; i++) {
      if (a[i] > a[i + 1]) {
        t = a[i];
        a[i] = a[i + 1];
        a[i + 1] = t;
      }
    }
  }
  min = 2147483647;
  for (j = 0; j < n - 1; j++) {
    if (a[j + 1] - a[j] < min) {
      min = a[j + 1] - a[j];
    }
  }
  return min;
}