int func0(int n) {
  int sum = 0;
  for (int i = 1; i <= n; i++) {
    int j = 2 * i;
    sum += j * j * j * j;
  }
  return sum;
}