long long _get_sum(int n, int k) {
  if (n < k) {
    return -1;
  }
  long long a = n - k + 1;
  long long b = n - 2 * k + 1;
  return a * (a + 1) / 2 + b * (b + 1) / 2;
}