long func0(int n) {
  int i, res = 1;
  for (i = 2; i <= n; i++) {
    res *= i;
    while (res % 10 == 0) res /= 10;
  }
  while (res >= 10) res /= 10;
  return floor((double)res);
}