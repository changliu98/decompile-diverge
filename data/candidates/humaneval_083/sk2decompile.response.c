int _pow(int n) {
  if (n < 1) {
    return 0;
  }
  if (n == 1) {
    return 1;
  }
  int result = 18;
  for (int i = 2; i < n; i++) {
    result *= 10;
  }
  return result;
}