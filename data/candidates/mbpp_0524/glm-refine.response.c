int __cdecl func0(int *arr, int n)
{
  int max = 0;
  
  // Allocate a temporary array (Variable Length Array) to store the maximum 
  // increasing subsequence sum ending at each index.
  int *sums = (int *)alloca(n * sizeof(int));

  // Initialize the sums array with the original array values.
  // This represents the base case where each subsequence starts with the element itself.
  for (int i = 0; i < n; ++i)
    sums[i] = arr[i];

  // Dynamic Programming approach to find the Maximum Sum Increasing Subsequence (MSIS)
  for (int i = 1; i < n; ++i)
  {
    for (int j = 0; j < i; ++j)
    {
      // If the current element is strictly greater than the previous element 
      // AND extending the subsequence yields a larger sum
      if (arr[i] > arr[j] && sums[i] < arr[i] + sums[j])
      {
        sums[i] = arr[i] + sums[j];
      }
    }
  }

  // Find the maximum value among all computed subsequence sums
  for (int i = 0; i < n; ++i)
  {
    if (max < sums[i])
      max = sums[i];
  }

  return max;
}