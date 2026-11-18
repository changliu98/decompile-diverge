int func0(int n) {
  int i, sum = 0;
  for (i = 2; i * i <= n; i++) {
    while (n % i == 0) {
      sum += i;
      n /= i;
    }
  }
  return sum + n;
}