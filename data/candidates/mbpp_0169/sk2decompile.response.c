int func0(int n) {
  if (n < 3) {
    return n;
  }
  int a = 1;
  int b = 2;
  int c;
  for (int i = 3; i <= n; i++) {
    c = a + 2 * b;
    a = b;
    b = c;
  }
  return b;
}