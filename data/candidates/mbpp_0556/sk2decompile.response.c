int func0(int *a, int n) {
  int i, j, c = 0;
  for (i = 0; i < n; i++) {
    for (j = i + 1; j < n; j++) {
      if ((a[i] ^ a[j]) % 2) {
        c++;
      }
    }
  }
  return c;
}