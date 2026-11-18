int *func0(int n) {
  int *a = malloc(n * sizeof(int));
  a[0] = n;
  for (int i = 1; i < n; i++) {
    a[i] = a[i - 1] + 2;
  }
  return a;
}