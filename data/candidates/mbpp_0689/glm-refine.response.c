int __cdecl func0(int *arr, int n)
{
  int min_jumps;
  
  // Check for edge cases: empty array or first element is 0
  if (n == 0 || arr[0] == 0)
  {
    min_jumps = INT_MAX;
  }
  else
  {
    // Variable Length Array (VLA) equivalent to the IDA stack allocation
    int dp[n];
    
    dp[0] = 0;
    for (int i = 1; i < n; ++i)
    {
      dp[i] = INT_MAX;
      for (int j = 0; j < i; ++j)
      {
        // If index 'i' is reachable from index 'j'
        if (i <= arr[j] + j && dp[j] != INT_MAX)
        {
          // Update the minimum jumps required to reach 'i'
          if (dp[j] + 1 < dp[i])
            dp[i] = dp[j] + 1;
            
          // The original code breaks immediately after finding the 
          // first valid 'j', preserving the exact semantics.
          break;
        }
      }
    }
    min_jumps = dp[n - 1];
  }
  
  return min_jumps;
}