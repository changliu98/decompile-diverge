int func0(int *a, int n, int m) {
  int i, prod = 1;
  for (i = 0; i < n; i++) {
    prod = (prod * (a[i] % m)) % m;
  }
  return prod % m;
}