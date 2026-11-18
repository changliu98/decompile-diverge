int func0(int *a, int n) {
  int i, j = -1;
  for (i = 1; i < n; i++) {
    if (a[i] < a[i - 1]) j = i;
  }
  return j;
}