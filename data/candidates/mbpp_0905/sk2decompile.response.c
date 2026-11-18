int func0(int n) {
  int result;
  result = factorial(n + 1, 2 * n);
  result /= factorial(1, n);
  return result;
}