int func0(int *a, int n, int x) {
  int l = 0;
  int m;
  while (l < n) {
    m = (n + l) / 2;
    if (a[m] < x)
      l = m + 1;
    else
      n = m;
  }
  return l;
}