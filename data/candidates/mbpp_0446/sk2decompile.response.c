int func0(int *a, int n, int *b, int m) {
  int i, j, c = 0;
  for (j = 0; j < n; j++) {
    for (i = 0; i < m; i++) {
      if (a[j] == b[i]) {
        c++;
        break;
      }
    }
  }
  return c;
}