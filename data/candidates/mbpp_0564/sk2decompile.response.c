int func0(int *a, int n) {
  int i, j, c = 0;
  for (j = 0; j < n; j++) {
    for (i = j + 1; i < n; i++) {
      if (a[j] != a[i]) {
        c++;
      }
    }
  }
  return c;
}