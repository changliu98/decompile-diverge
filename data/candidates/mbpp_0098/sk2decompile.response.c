double func0(int *a, int n) {
  int i;
  double sum = 1.0;
  for (i = 0; i < n; i++) {
    sum *= a[i];
  }
  return sum / n;
}