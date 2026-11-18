int _find(int *a, int l, int r) {
  if (l > r) return r + 1;
  if (l == a[l]) {
    int m = (r + l) / 2;
    if (a[m] == m)
      return _find(a, m + 1, r);
    else
      return _find(a, l, m);
  } else
    return l;
}