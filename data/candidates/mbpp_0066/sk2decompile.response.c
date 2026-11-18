int func0(int *a, int n) {
  int i, count = 0;
  for (i = 0; i < n; i++) {
    if (a[i] >= 0) {
      count++;
    }
  }
  return count;
}