int _find(int *a, int l, int r) {
  if (l > r) return l;
  int m = l + (r - l) / 2;
  if (a[m] == m)
    return _find(a, m + 1, r);
  else
    return _find(a, l, m - 1);
}