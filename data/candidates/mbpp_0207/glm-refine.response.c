int __cdecl func0(const char *str)
{
  int n = strlen(str);
  int size = n + 1;
  
  // Allocate a 2D VLA (Variable Length Array) for the DP table
  int dp[size][size];
  
  // Initialize the DP table with 0s
  for (int i = 0; i <= n; ++i)
  {
    for (int j = 0; j <= n; ++j)
    {
      dp[i][j] = 0;
    }
  }
  
  // Fill the DP table
  for (int i = 1; i <= n; ++i)
  {
    for (int j = 1; j <= n; ++j)
    {
      // Characters match and indices are different
      if (str[i - 1] == str[j - 1] && i != j)
      {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      }
      else
      {
        // Characters don't match or indices are the same
        if (dp[i - 1][j] >= dp[i][j - 1])
          dp[i][j] = dp[i - 1][j];
        else
          dp[i][j] = dp[i][j - 1];
      }
    }
  }
  
  return dp[n][n];
}