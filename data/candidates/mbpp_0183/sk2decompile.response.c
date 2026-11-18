int func0(int *a, int n, int k) {
  int i, j, c = 0;
  for (i = 0; i < n; i++) {
    for (j = i + 1; j < n; j++) {
      if (a[i] - a[j] == k || a[j] - a[i] == k) {
        c++;
      }
    }
  }
  return c;
}