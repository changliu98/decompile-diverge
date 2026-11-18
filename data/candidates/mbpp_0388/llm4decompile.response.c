int func0(int n) {
  while (n > 0) {
    if ((n & (n - 1)) == 0) {
      return n;
    }
    n--;
  }
  return 0;
}