int func0(int n) {
  int i, sum = 0;
  for (i = 1; i <= n; i++) {
    sum += i * i * i * i * i;
  }
  return sum;
}