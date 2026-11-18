int func0(int *a, int n) {
  int i;
  for (i = 1; i < n; i++) {
    if (a[i] < a[i - 1]) {
      return 0;
    }
  }
  return 1;
}