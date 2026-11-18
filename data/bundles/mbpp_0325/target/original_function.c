int func0(int n) {
  if (n <= 3) {
    return n;
  }
  int res = n;
  for (int x = 1; x <= n; x++) {
    int temp = x * x;
    if (temp > n) {
      break;
    } else {
      res = (res < (1 + func0(n - temp))) ? res : (1 + func0(n - temp));
    }
  }
  return res;
}