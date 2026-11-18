int func0(int n) {
  int i, j, count;
  count = 0;
  for (i = 0; i < n; i++) {
    if (i % 11 == 0 || i % 13 == 0) {
      for (j = i; j > 0; j /= 10) {
        if (j % 10 == 7) count++;
      }
    }
  }
  return count;
}