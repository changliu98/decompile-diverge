double func0(int n) {
  int i;
  double a = 1.0;
  double sum = 1.0;
  for (i = 1; i <= n; i++) {
    a = a * (n + 1 - i) / i;
    sum += a * a;
  }
  return sum;
}