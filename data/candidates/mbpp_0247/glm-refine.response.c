int __cdecl func0(char *str)
{
  int n = strlen(str);
  if (n == 0)
    return 0;

  // The original code allocates a VLA of size n x n using a 1D byte array 
  // and manual pointer arithmetic. We can cleanly represent it as a 2D VLA.
  int dp[n][n];

  // Base case: Substrings of length 1 are palindromes of length 1
  for (int i = 0; i < n; ++i)
    dp[i][i] = 1;

  // Iterate over all possible substring lengths
  for (int len = 2; len <= n; ++len)
  {
    for (int i = 0; i <= n - len; ++i)
    {
      int j = i + len - 1;

      if (str[i] == str[j])
      {
        if (len == 2)
        {
          dp[i][j] = 2;
        }
        else
        {
          // If the ends match, add 2 to the longest palindromic subsequence inside
          dp[i][j] = dp[i + 1][j - 1] + 2;
        }
      }
      else
      {
        // If the ends don't match, take the maximum of excluding either end
        int left = dp[i][j - 1];
        int right = dp[i + 1][j];
        dp[i][j] = (left > right) ? left : right;
      }
    }
  }

  // The answer for the entire string is stored in the top-right corner of the table
  return dp[0][n - 1];
}