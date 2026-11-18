int func0(int *a, int n) {
  int i, sum = 0;
  for (i = 0; i < n; i++) {
    if (i % 3 == 0) {
      sum += a[i] * a[i];
    } else if (i % 4 == 0) {
      sum += a[i] * a[i] * a[i];
    } else {
      sum += a[i];
    }
  }
  return sum;
}