int func0(int n) {
  int ret = 0;
  while (n > 0) {
    if ((n & (n - 1)) == 0) {
      ret = n;
      break;
    }
    n--;
  }
  return ret;
}