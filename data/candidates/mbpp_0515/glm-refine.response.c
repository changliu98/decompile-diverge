bool __cdecl func0(int *arr, int n, int m)
{
  bool *dp;       // Replaces v6
  bool *next_dp;  // Replaces v5/v11
  int i, j;        // Loop counters

  // If the number of elements is greater than the modulo base, 
  // it's guaranteed that we can form a sum divisible by m.
  if (n > m)
    return true;

  // Allocate Variable Length Arrays (VLAs) on the stack for the DP arrays.
  // The original code manually aligned the stack pointer to 16 bytes.
  dp = (bool *)alloca(m);
  next_dp = (bool *)alloca(m);

  // Initialize the DP array to false
  for (i = 0; i < m; ++i)
    dp[i] = false;

  for (i = 0; i < n; ++i)
  {
    // If a sum divisible by m has already been found, return true early
    if (dp[0])
      return true;

    // Initialize the next state array to false
    for (j = 0; j < m; ++j)
      next_dp[j] = false;

    // Transition states: if a sum modulo m is currently reachable (dp[j]),
    // then adding the current element arr[i] makes (arr[i] + j) % m reachable.
    for (j = 0; j < m; ++j)
    {
      if (dp[j] && !dp[(arr[i] + j) % m])
        next_dp[(arr[i] + j) % m] = true;
    }

    // Merge the newly reachable states back into the main DP array
    for (j = 0; j < m; ++j)
    {
      if (next_dp[j])
        dp[j] = true;
    }

    // The current element itself forms a sum, so its modulo is reachable
    dp[arr[i] % m] = true;
  }

  // After processing all elements, check if a sum modulo m == 0 is reachable
  return dp[0];
}