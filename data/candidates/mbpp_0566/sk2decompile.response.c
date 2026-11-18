int func0(int n) {
  if (n == 0) {
    return 0;
  } else {
    return func0(n / 10) + n % 10;
  }
}