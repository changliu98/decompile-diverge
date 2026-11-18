int func0(int n) {
  int a[1000];
  int m = n;
  memset(a, 0, sizeof(a));
  a[0] = 0;
  a[1] = 1;
  int i;
  for (i = 2; i <= m; i++) {
    a[i] = a[i - 1] + a[i - 2];
  }
  return a[m];
}