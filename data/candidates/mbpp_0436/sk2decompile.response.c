int func0(int *a, int n) {
  int i;
  for (i = 0; i < n; i++) {
    if (a[i] < 0) {
      return a[i];
    }
  }
  return 0;
}