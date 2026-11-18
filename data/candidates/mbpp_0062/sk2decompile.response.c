int func0(int *a, int n) {
  int min = 2147483647;
  for (int i = 0; i < n; i++) {
    if (a[i] < min) {
      min = a[i];
    }
  }
  return min;
}