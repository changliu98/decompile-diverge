int func0(int n) {
  int i, sum = 0;
  for (i = 1; i < n; i++) {
    if (n % i == 0) {
      sum += i;
    }
  }
  if (sum > n) {
    return 1;
  } else {
    return 0;
  }
}