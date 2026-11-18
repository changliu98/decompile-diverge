int func0(double *x, int n) {
  int sum = 0;
  int i;
  for (i = 0; i < n; i++) {
    sum += round(x[i]);
  }
  return sum * n;
}