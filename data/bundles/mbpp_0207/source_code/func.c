

#include <stdio.h>

#include <string.h>

#include <assert.h>



int func0(char *str) {
  int n = strlen(str);
  int dp[n + 1][n + 1];
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      dp[i][j] = 0;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (str[i - 1] == str[j - 1] && i != j) {
        dp[i][j] = 1 + dp[i - 1][j - 1];
      } else {
        dp[i][j] = (dp[i][j - 1] > dp[i - 1][j]) ? dp[i][j - 1] : dp[i - 1][j];
      }
    }
  }
  return dp[n][n];
}
