void func0(int *a, int n, int *b) {
  int *c = malloc(sizeof(int) * (n / 3 + 1));
  int m = 0;
  for (int i = 0; i * 3 < n; i++) {
    c[i] = a[i * 3];
    m++;
  }
  for (int i = 0; i < m - 1; i++) {
    int min = i;
    for (int j = i + 1; j < m; j++) {
      if (c[j] < c[min]) {
        min = j;
      }
    }
    if (min != i) {
      int tmp = c[i];
      c[i] = c[min];
      c[min] = tmp;
    }
  }
  for (int i = 0; i < n; i++) {
    b[i] = i % 3 == 0 ? c[i / 3] : a[i];
  }
  free(c);
}