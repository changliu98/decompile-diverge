int __cdecl func0(int n)
{
  // Allocate a Variable Length Array (VLA) of size n + 1
  int *dp = (int *)alloca((n + 1) * sizeof(int));
  
  // Base cases
  dp[0] = 0;
  dp[1] = 1;

  // Dynamic programming loop to populate the rest of the array
  for (int i = 2; i <= n; ++i)
  {
    // Default value
    dp[i] = i;

    // Calculate the sum of subproblems for i/2, i/3, i/4, and i/5
    int sum = dp[i / 2] + dp[i / 3] + dp[i / 4] + dp[i / 5];

    // Keep the maximum between the default value and the computed sum
    if (sum > dp[i])
      dp[i] = sum;
  }

  return dp[n];
}