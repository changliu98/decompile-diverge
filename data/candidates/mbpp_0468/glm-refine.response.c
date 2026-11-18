int __cdecl func0(int *arr, int n)
{
  // Allocate a Variable Length Array (VLA) to store the maximum product ending at each index.
  // IDA Pro originally decompiled this as pointer arithmetic on the stack pointer.
  int *dp = (int *)alloca((4 * (unsigned int)n + 15) & 0xFFFFFFFFFFFFFFF0LL);
  
  // Initialize the dp array with the values from the input array.
  for (int i = 0; i < n; ++i)
    dp[i] = arr[i];

  // Iterate through the array to calculate the maximum product of an increasing subsequence.
  for (int i = 1; i < n; ++i)
  {
    for (int j = 0; j < i; ++j)
    {
      // If the current element is greater than the previous element,
      // and multiplying them yields a greater product than currently stored.
      if (arr[i] > arr[j] && dp[i] < arr[i] * dp[j])
        dp[i] = arr[i] * dp[j];
    }
  }

  // Find the maximum value in the dp array.
  int maxVal = dp[0];
  for (int i = 1; i < n; ++i)
  {
    if (dp[i] > maxVal)
      maxVal = dp[i];
  }

  return maxVal;
}