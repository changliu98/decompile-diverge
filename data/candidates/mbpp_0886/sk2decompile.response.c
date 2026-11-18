double func0(int *a, int n) {
  int i, sum = 0;
  for (i = 0; i < n; i++) {
    sum += a[i];
  }
  return (double)sum / (double)n;
}