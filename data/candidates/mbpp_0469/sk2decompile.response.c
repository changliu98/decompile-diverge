int _maxProfit(int price[], int n, int k) {
  int profit[k + 1][n];
  int i, j, l;
  for (j = 0; j <= k; j++) {
    for (i = 0; i < n; i++) {
      if (j == 0 || i == 0)
        profit[j][i] = 0;
      else {
        int max = 0;
        for (l = 0; l < i; l++) {
          int curr = profit[j - 1][l] + price[i] - price[l];
          if (max < curr) max = curr;
        }
        profit[j][i] =
            max > profit[j - 1][i] ? max : profit[j - 1][i];
      }
    }
  }
  return profit[k][n - 1];
}