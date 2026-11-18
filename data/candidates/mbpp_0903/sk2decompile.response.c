int func0(int n) {
  int i, j, c = 0;
  for (i = 1; i <= n; i++) {
    for (j = i; j; j /= 2) {
      if (j % 2 == 0) c++;
    }
  }
  return c;
}