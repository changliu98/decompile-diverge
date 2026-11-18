int func0(int n) {
  int count = 0;
  for (int i = 1; i < 2 * n; i++) {
    for (int j = 1; j < 2 * n; j++) {
      if (i * i + j * j <= 4 * n * n) {
        count++;
      }
    }
  }
  return count;
}