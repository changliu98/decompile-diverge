int func0(int n) {
  int m = n + 1;
  int i = 2;
  int sum = m / 2;
  while (i <= m) {
    sum += (m / i / 2) * i;
    if (m / i % 2 != 0) {
      sum += m % i;
    }
    i *= 2;
  }
  return sum;
}