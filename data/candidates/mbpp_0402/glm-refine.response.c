modulo p
int __cdecl func0(int n, int r, int p)
{
  // VLA representing the dynamic programming array for the current row of Pascal's triangle
  int dp[r + 1]; 

  // Initialize the array with zeros
  for (int i = 0; i <= r; ++i)
    dp[i] = 0;

  // Base case: C(i, 0) = 1
  dp[0] = 1;

  // Build the triangle row by row up to n
  for (int i = 1; i <= n; ++i)
  {
    // The inner loop only needs to go up to min(i, r) because C(i, k) = 0 for k > i
    int limit = (i >= r) ? r : i;

    // Update the row in reverse to safely use values from the previous row (i-1)
    for (int j = limit; j > 0; --j)
      dp[j] = (dp[j - 1] + dp[j]) % p;
  }

  // The result is C(n, r) modulo p
  return dp[r];
}