double func0(int n) {
  if (n < 0) {
    return 0;
  }
  return 1.0 / pow(2.0, (double)n) + func0(n - 1);
}