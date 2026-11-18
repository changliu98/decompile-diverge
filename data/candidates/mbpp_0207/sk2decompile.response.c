int _longest_palindromic_subsequence(char *str) {
  int len = strlen(str);
  int dp[len + 1][len + 1];
  int i, j, k;
  for (i = 0; i <= len; i++) {
    for (j = 0; j <= len; j++) {
      dp[i][j] = 0;
    }
  }
  for (i = 1; i <= len; i++) {
    for (j = 1; j <= len; j++) {
      if (str[i - 1] == str[j - 1] && i != j) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = dp[i - 1][j] > dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1];
      }
    }
  }
  return dp[len][len];
}