int __cdecl func0(int n)
{
  // Allocate a Variable Length Array (VLA) of size n + 1.
  // The original code used pointer arithmetic to manually allocate this on the stack.
  int *dp = (int *)alloca((4LL * (unsigned int)(n + 1) + 15) & 0xFFFFFFFFFFFFFFF0LL);
  
  // Base cases
  dp[0] = 0;
  dp[1] = 1;

  // Compute the sequence iteratively
  for (int i = 2; i <= n; ++i)
  {
    // The compiler unrolled the additions into intermediate stack variables (v4, v5).
    // We can simplify this to a single expression.
    int val = dp[i / 4] + dp[i / 3] + dp[i / 2];

    // Enforce a minimum bound: if the computed value is less than i, use i
    if (val < i)
      val = i;

    dp[i] = val;
  }

  return dp[n];
}