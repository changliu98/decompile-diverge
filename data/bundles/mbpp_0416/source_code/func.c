

#include <stdio.h>

#include <assert.h>



#define MAX 1000000



int func0(int n) {
  int dp[n + 1];
  dp[0] = 0;
  dp[1] = 1;
  for (int i = 2; i <= n; i++) {
    dp[i] = dp[i / 2] + dp[i / 3] + dp[i / 4];
    if (dp[i] < i) {
      dp[i] = i;
    }
  }
  return dp[n];
}
