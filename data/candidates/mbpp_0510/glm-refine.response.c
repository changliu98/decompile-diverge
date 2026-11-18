int __cdecl func0(int *arr, int n, int k)
{
  // The original code manually allocates a 2D VLA on the stack:
  // dp[k + 1][n + 1]
  int dp[k + 1][n + 1];

  // Initialize all elements of the DP table to 0
  for (int i = 0; i <= k; ++i)
  {
    for (int j = 0; j <= n; ++j)
    {
      dp[i][j] = 0;
    }
  }

  // Fill the DP table
  for (int i = 1; i <= k; ++i)
  {
    for (int j = 1; j <= n; ++j)
    {
      // Inherit the value from the previous element in the row
      dp[i][j] = dp[i][j - 1];
      
      int val = arr[j - 1];
      // If the current element is a valid divisor of i
      if (val > 0 && val <= i)
      {
        // Add the count from the subproblem plus 1 for the current valid division
        dp[i][j] += dp[i / val][j - 1] + 1;
      }
    }
  }

  // Return the bottom-right cell of the DP table
  return dp[k][n];
}