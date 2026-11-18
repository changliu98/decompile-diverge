int func0(int *a, int n) {
  int i, j, sum = 0;
  for (i = 0; i < n; i++) {
    for (j = i + 1; j < n; j++) {
      sum += a[i] ^ a[j];
    }
  }
  return sum;
}