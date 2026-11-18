int func0(int *a, int n, int x, int y) {
  int i, count = 0;
  for (i = 0; i < n; i++) {
    if (a[i] >= x && a[i] <= y) {
      count++;
    }
  }
  return count;
}