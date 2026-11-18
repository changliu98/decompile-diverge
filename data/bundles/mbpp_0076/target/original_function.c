int func0(int m, int n) {
  if (n < m) {
    int temp = m;
    m = n;
    n = temp;
  }
  return (int)(m * (m + 1) * (2 * m + 1) / 6 + (n - m) * m * (m + 1) / 2);
}