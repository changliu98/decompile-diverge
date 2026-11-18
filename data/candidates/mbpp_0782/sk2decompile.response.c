int _count_inversions(int *a, int n) {
  int i, count = 0;
  for (i = 0; i < n; i++) {
    count += (i + 1) * (n - i) * (i + 1) / 2;
    count += a[i] * (i + 1) * (n - i);
  }
  return count;
}