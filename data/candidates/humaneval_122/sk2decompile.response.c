int func0(int *a, int n) {
  int i, sum = 0;
  for (i = 0; i < n; i++) {
    if (a[i] >= -99 && a[i] <= 99) {
      sum += a[i];
    }
  }
  return sum;
}