int func0(int n) {
  int i;
  for (i = 2; i * i <= n; i++) {
    while (n % i == 0 && i < n) {
      n /= i;
    }
  }
  return n;
}