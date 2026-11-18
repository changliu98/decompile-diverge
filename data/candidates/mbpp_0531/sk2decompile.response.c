int func0(int coins[], int n, int amount) {
  if (amount == 0) return 0;
  int min = 2147483647;
  for (int i = 0; i < n; i++) {
    if (coins[i] <= amount) {
      int res = func0(coins, n, amount - coins[i]);
      if (res != 2147483647 && res + 1 < min) min = res + 1;
    }
  }
  return min;
}