int func0(int *a, int n, int p) {
  int i, c = 0;
  for (i = 0; i < n; i++) {
    if ((a[i] * a[i]) % p == 1) {
      c++;
    }
  }
  return c;
}