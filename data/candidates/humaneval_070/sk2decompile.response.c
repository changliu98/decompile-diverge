void func0(int *a, int n, int *b) {
  int i, j, t, k;
  for (i = 0; i < n - 1; i++) {
    for (j = i + 1; j < n; j++) {
      if (a[i] > a[j]) {
        t = a[i];
        a[i] = a[j];
        a[j] = t;
      }
    }
  }
  i = 0;
  j = n - 1;
  k = 0;
  while (i <= j) {
    b[k++] = a[i++];
    if (i == j) {
      b[k++] = a[i++];
    } else {
      b[k++] = a[j--];
    }
  }
}