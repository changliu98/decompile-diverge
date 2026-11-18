int func0(int n, int *a) {
  int i, min, count;
  min = a[0];
  count = 1;
  for (i = 1; i < n; i++) {
    if (a[i] < min) {
      min = a[i];
      count = 1;
    } else if (a[i] == min) {
      count++;
    }
  }
  return count;
}