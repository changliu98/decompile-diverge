long func0(int n) {
  int i;
  long sum = 0;
  for (i = 1; i <= n; i++) {
    sum += 2 * i * 2 * i * 2 * i * 2 * i;
  }
  return sum;
}