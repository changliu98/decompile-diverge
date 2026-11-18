int func0(int n) {
  int i, sum = 1;
  for (i = 2; i < n; i++) {
    if (n % i == 0) {
      sum += i;
    }
  }
  return sum;
}