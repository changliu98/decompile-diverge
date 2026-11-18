int __cdecl func0(int *arr, int N, int K)
{
  int *dp;
  int result;
  int i;

  // Sort the array in ascending order
  qsort(arr, N, sizeof(int), (__compar_fn_t)cmpfunc);

  // Allocate memory for the dynamic programming array
  dp = (int *)malloc(sizeof(int) * N);
  
  // Base case
  dp[0] = 0;

  // Iterate through the array to find the maximum sum of valid pairs
  for (i = 1; i < N; ++i)
  {
    // By default, carry forward the previous maximum sum
    dp[i] = dp[i - 1];

    // If the difference between adjacent elements is strictly less than K
    if (arr[i] - arr[i - 1] < K)
    {
      if (i < 2)
      {
        // For the first pair (i=1), compare picking this pair vs the previous max
        dp[i] = (arr[i - 1] + arr[i] > dp[i]) ? arr[i - 1] + arr[i] : dp[i];
      }
      else
      {
        // For subsequent pairs, picking this pair adds to the max sum up to i-2
        int current_pair_sum = arr[i - 1] + arr[i] + dp[i - 2];
        dp[i] = (current_pair_sum > dp[i]) ? current_pair_sum : dp[i];
      }
    }
  }

  result = dp[N - 1];
  free(dp);
  return result;
}