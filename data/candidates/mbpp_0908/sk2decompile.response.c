int func0(int *a, int n) {
  int i;
  for (i = 0; i < n; i++) {
    if (a[i] == i) {
      return i;
    }
  }
  return -1;
}