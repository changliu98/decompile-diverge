int func0(int n) {
  int i, sum = 0;
  for (i = 1; i <= n; i++) {
    sum += 2 * i * 2 * i * 2 * i;
  }
  return sum;
}