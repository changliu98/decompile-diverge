int __cdecl func0(int *arr, int n)
{
  int max_sum;
  int *dp_inc; // Replaces v4
  int *dp_dec; // Replaces v3
  int i, j;

  if (n <= 0)
    return -99999999;

  // Allocate Variable Length Arrays (VLAs) to match the original stack allocations
  dp_inc = (int *)alloca((4 * (unsigned int)n + 15) & 0xFFFFFFFFFFFFFFF0LL);
  dp_dec = (int *)alloca((4 * (unsigned int)n + 15) & 0xFFFFFFFFFFFFFFF0LL);

  // Initialize the increasing subsequence DP array
  for (i = 0; i < n; ++i)
    dp_inc[i] = arr[i];

  // Compute the Maximum Sum Increasing Subsequence (MSIS) ending at each index
  for (i = 1; i < n; ++i)
  {
    for (j = 0; j < i; ++j)
    {
      if (arr[i] > arr[j] && dp_inc[i] < arr[i] + dp_inc[j])
        dp_inc[i] = arr[i] + dp_inc[j];
    }
  }

  // Initialize the decreasing subsequence DP array
  for (i = 0; i < n; ++i)
    dp_dec[i] = arr[i];

  // Compute the Maximum Sum Decreasing Subsequence (MSDS) starting at each index
  for (i = 1; i < n; ++i)
  {
    for (j = 0; j < i; ++j)
    {
      // i and j are offsets from the end of the array (na - i - 1 and na - j - 1)
      if (arr[n - i - 1] > arr[n - j - 1] && dp_dec[n - i - 1] < arr[n - i - 1] + dp_dec[n - j - 1])
        dp_dec[n - i - 1] = arr[n - i - 1] + dp_dec[n - j - 1];
    }
  }

  // Find the maximum sum of a bitonic subsequence
  max_sum = -99999999;
  for (i = 0; i < n; ++i)
  {
    // The peak element arr[i] is counted in both dp_inc and dp_dec, so subtract it once
    if (max_sum < dp_dec[i] + dp_inc[i] - arr[i])
      max_sum = dp_dec[i] + dp_inc[i] - arr[i];
  }

  return max_sum;
}