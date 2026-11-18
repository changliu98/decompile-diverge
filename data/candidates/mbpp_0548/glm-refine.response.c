int __cdecl func0(int *arr, int n)
{
  // Allocate a Variable Length Array (VLA) of size 'n' on the stack.
  // The original code used pointer arithmetic to manually allocate stack space.
  int *dp = (int *)alloca(n * sizeof(int));

  // Initialize all elements in the dp array to 1
  for (int i = 0; i < n; ++i)
    dp[i] = 1;

  // Core logic: Dynamic Programming approach to find the Longest Increasing Subsequence (LIS)
  for (int i = 1; i < n; ++i)
  {
    for (int j = 0; j < i; ++j)
    {
      // If the current element is greater than the previous element,
      // and the subsequence length can be extended, update it.
      if (arr[i] > arr[j] && dp[i] < dp[j] + 1)
        dp[i] = dp[j] + 1;
    }
  }

  // Find the maximum value in the dp array
  int maximum = 0;
  for (int i = 0; i < n; ++i)
  {
    if (dp[i] > maximum)
      maximum = dp[i];
  }

  return maximum;
}