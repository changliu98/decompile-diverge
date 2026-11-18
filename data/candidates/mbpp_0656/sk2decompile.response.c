int func0(int *a, int *b, int n) {
  sort(a, n);
  sort(b, n);
  int i, sum = 0;
  for (i = 0; i < n; i++) {
    sum += abs(a[i] - b[i]);
  }
  return sum;
}