void func0(int *a, int n, int *b) {
  int i;
  qsort(a, n, sizeof(int), cmp);
  for (i = 0; i < n; i++) {
    b[i] = a[i];
  }
}