int func0(int *a, int n) {
  int i, c = 0;
  for (i = 0; i < n / 2; i++) {
    if (a[i] != a[n - 1 - i]) {
      c++;
    }
  }
  return c;
}