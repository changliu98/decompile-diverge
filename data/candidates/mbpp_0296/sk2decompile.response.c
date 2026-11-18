int func0(int *a, int n) {
  int count = 0;
  int i, j;
  for (i = 0; i < n; i++) {
    for (j = i + 1; j < n; j++) {
      if (a[i] > a[j]) {
        count++;
      }
    }
  }
  return count;
}