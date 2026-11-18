int func0(int a[], int n)
{
  int l = 0;
  int r = n - 1;
  int m;
  while (l <= r) {
    m = (l + r)/2;
    if (a[m] != m + 1 && a[m - 1] == m)
      return m + 1;
    if (a[m] == m + 1)
      l = m + 1;
    else
      r = m - 1;
  }
  return -1;
}