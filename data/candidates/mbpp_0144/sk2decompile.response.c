int func0(int *a, int n) {
  int i, sum = 0;
  for (i = n - 1; i >= 0; i--) {
    sum += a[i] * i - a[i] * (n - 1 - i);
  }
  return sum;
}