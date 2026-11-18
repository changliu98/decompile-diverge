int func0(int a[], int b[], int n) {
  sort(a, n);
  sort(b, n);
  int sum = 0;
  for (int i = 0; i < n; i++) {
    sum += abs(a[i] - b[i]);
  }
  return sum;
}