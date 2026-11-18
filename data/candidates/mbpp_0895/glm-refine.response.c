int __cdecl func0(int *A, int n)
{
  int max_val; 
  int *dp; 
  int option1, option2, option3;
  int i;
  unsigned __int64 na;
  _BYTE *v14;
  
  na = (unsigned int)n;
  if ( n == 1 )
    return *A;

  // Allocate Variable Length Array (VLA) on the stack
  // IDA's decompiler misinterprets the stack allocation, but it boils down to:
  // int dp[na];
  v14 = (_BYTE *)&dp;
  dp = (int *)v14 - ((4LL * na + 15) & 0xFFFFFFFFFFFFFFF0LL);

  // Base cases for the dynamic programming array
  dp[0] = A[0];
  dp[1] = (A[0] <= A[1]) ? A[1] : A[0];

  // Iterate through the array to find the maximum sum
  for ( i = 2; i < (int)na; ++i )
  {
    option1 = dp[i - 1];
    option2 = A[i] + dp[i - 2];
    option3 = A[i];

    // dp[i] = max(option1, option2, option3)
    dp[i] = (option1 > option2) ? option1 : option2;
    dp[i] = (dp[i] > option3) ? dp[i] : option3;
  }

  return dp[n - 1];
}