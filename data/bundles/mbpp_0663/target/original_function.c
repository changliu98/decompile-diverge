int func0(int n, int x, int y) {
  int ans = INT_MIN;
  for (int k = 0; k <= n; k++) {
    if (k % x == y) {
      if (ans < k) {
        ans = k;
      }
    }
  }
  return ((ans >= 0 && ans <= n) ? ans : -1);
}