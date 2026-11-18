int func0(int n) {
  int a[100];
  int m = n;
  a[0] = 0;
  a[1] = 0;
  a[2] = 2;
  a[3] = 0;
  for (int i = 4; i <= m; i++) {
    a[i] = a[i - 4] + a[i - 3] + a[i - 2] + a[i - 1];
  }
  return a[m];
}