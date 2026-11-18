

#include <stdio.h>

#include <assert.h>



int func0(int a[], int n) {
  int dp[n];
  dp[n - 1] = 1;
  for (int i = n - 2; i >= 0; i--) {
    int mxm = 0;
    for (int j = i + 1; j < n; j++) {
      if (a[j] % a[i] == 0 || a[i] % a[j] == 0) {
        if (mxm < dp[j]) {
          mxm = dp[j];
        }
      }
    }
    dp[i] = 1 + mxm;
  }
  int max_val = dp[0];
  for (int i = 1; i < n; i++) {
    if (max_val < dp[i]) {
      max_val = dp[i];
    }
  }
  return max_val;
}
