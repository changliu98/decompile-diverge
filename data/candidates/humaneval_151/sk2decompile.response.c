long func0(float *a, int n) {
  long sum = 0;
  for (int i = 0; i < n; i++) {
    if (fabs(a[i] - round(a[i])) < 0.0001 && a[i] > 0 &&
        (int)round(a[i]) % 2 == 1) {
      int x = (int)round(a[i]);
      sum += x * x;
    }
  }
  return sum;
}