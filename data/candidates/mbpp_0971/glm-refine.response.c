int __cdecl func0(int n, int a, int b, int c)
{
  // The original code allocated a Variable Length Array (VLA) of size n + 10.
  // We replace it with a standard dynamically allocated array for clarity and safety.
  int *dp = (int *)malloc((n + 10) * sizeof(int));
  
  // Initialize all states to "unreachable" (-1), except for the starting state (0).
  for (int i = 0; i < n + 10; ++i)
    dp[i] = -1;
  dp[0] = 0;

  // Iterate through all possible states up to n.
  // This is a shortest-path (BFS-like) algorithm on a 1D grid, similar to the 
  // coin change problem where you want to reach the sum `n` using coins {a, b, c}.
  for (int i = 0; i <= n; ++i)
  {
    if (dp[i] != -1) 
    {
      // Transition using step 'a'
      if (a + i <= n) 
      {
        if (dp[i] + 1 < dp[a + i] || dp[a + i] == -1)
          dp[a + i] = dp[i] + 1;
      }
      
      // Transition using step 'b'
      if (b + i <= n) 
      {
        if (dp[i] + 1 < dp[b + i] || dp[b + i] == -1)
          dp[b + i] = dp[i] + 1;
      }
      
      // Transition using step 'c'
      if (c + i <= n) 
      {
        if (dp[i] + 1 < dp[c + i] || dp[c + i] == -1)
          dp[c + i] = dp[i] + 1;
      }
    }
  }
  
  // Store the result before freeing the allocated memory
  int result = dp[n];
  free(dp);
  
  return result;
}