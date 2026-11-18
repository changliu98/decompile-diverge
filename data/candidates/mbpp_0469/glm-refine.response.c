int __cdecl func0(int *price, int n, int k)
{
  // Allocate a 2D array equivalent to int dp[k + 1][n]
  // Using calloc to safely simulate the zero-initialization of the VLA
  int *dp = (int *)calloc((k + 1) * n, sizeof(int));
  if (!dp) return 0;

  for (int i = 0; i <= k; ++i)
  {
    for (int j = 0; j < n; ++j)
    {
      if (i != 0 && j != 0)
      {
        int max_so_far = 0;
        for (int x = 0; x < j; ++x)
        {
          // dp[i - 1][x] + price[j] - price[x]
          int curr_price = dp[(i - 1) * n + x] + price[j] - price[x];
          if (max_so_far < curr_price)
            max_so_far = curr_price;
        }
        
        // dp[i][j] = max(dp[i][j - 1], max_so_far)
        if (dp[i * n + j - 1] <= max_so_far)
          dp[i * n + j] = max_so_far;
        else
          dp[i * n + j] = dp[i * n + j - 1];
      }
      else
      {
        // dp[i][j] = 0
        dp[i * n + j] = 0;
      }
    }
  }

  // Result is dp[k][n - 1]
  int result = dp[k * n + n - 1];
  free(dp);
  return result;
}