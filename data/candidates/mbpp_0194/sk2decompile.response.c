int func0(int n) {
  int sum = 0, m = 1, r;
  while (n) {
    r = n % 10;
    n = n / 10;
    sum = sum + r * m;
    m = m * 8;
  }
  return sum;
}