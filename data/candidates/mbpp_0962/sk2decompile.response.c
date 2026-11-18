int func0(int n, int m) {
  int m1 = m / 2;
  int m2 = m1 + 1;
  int n1 = n - 1;
  int n2 = n1 / 2;
  return m1 * m2 - n2 * (n + 1) / 2;
}