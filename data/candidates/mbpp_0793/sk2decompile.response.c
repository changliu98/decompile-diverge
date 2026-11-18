int func0(int *a, int x, int n) {
  int l, r, m, res;
  l = 0;
  r = n - 1;
  res = -1;
  while (l <= r) {
    m = (r + l) / 2;
    if (a[m] > x)
      r = m - 1;
    else {
      if (a[m] >= x) res = m;
      l = m + 1;
    }
  }
  return res;
}