

#include <stdio.h>

#include <assert.h>



int func0(int arr[], int n, int k) {
  int dp[k + 1][n + 1];
  for (int i = 0; i <= k; i++) {
    for (int j = 0; j <= n; j++) {
      dp[i][j] = 0;
    }
  }
  for (int i = 1; i <= k; i++) {
    for (int j = 1; j <= n; j++) {
      dp[i][j] = dp[i][j - 1];
      if (arr[j - 1] <= i && arr[j - 1] > 0) {
        dp[i][j] += dp[i / arr[j - 1]][j - 1] + 1;
      }
    }
  }
  return dp[k][n];
}
