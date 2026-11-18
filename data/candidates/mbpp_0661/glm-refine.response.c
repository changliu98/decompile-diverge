int __cdecl func0(int *arr, int n)
{
  if (n <= 0)
    return 0; // Edge case: implicit return for empty array

  // Allocate Variable Length Array (VLA) for dynamic programming states
  int *dp = (int *)alloca((4LL * (unsigned int)n + 15) & 0xFFFFFFFFFFFFFFF0LL);

  // Base cases
  if (n >= 1)
    dp[0] = arr[0];

  if (n >= 2)
    dp[1] = arr[0] + arr[1];

  if (n > 2)
  {
    // dp[2] = max(dp[1], arr[0] + arr[2], arr[1] + arr[2])
    int max1 = dp[1];
    int max2 = arr[0] + arr[2];
    int max3 = arr[1] + arr[2];
    dp[2] = (max1 > max2) ? max1 : max2;
    if (dp[2] < max3)
      dp[2] = max3;
  }

  // Fill the rest of the dp array
  for (int i = 3; i < n; ++i)
  {
    // dp[i] = max(dp[i-1], arr[i] + dp[i-2], arr[i] + arr[i-1] + dp[i-3])
    int max1 = dp[i - 1];
    int max2 = arr[i] + dp[i - 2];
    int max3 = arr[i] + arr[i - 1] + dp[i - 3];

    int best = (max1 > max2) ? max1 : max2;
    if (best < max3)
      best = max3;

    dp[i] = best;
  }

  return dp[n - 1];
}