int __cdecl func0(int *arr, int n)
{
  int *lis; // v4: Length of Longest Increasing Subsequence ending at i
  int *lds; // v5: Length of Longest Decreasing Subsequence starting at i
  int maximum;
  int i, j;

  // Allocate memory for the DP arrays. 
  // Note: The original decompilation allocated n+1 elements and initialized n+1 elements,
  // so we preserve this exact behavior to avoid any out-of-bounds semantic changes.
  lis = (int *)malloc((n + 1) * sizeof(int));
  lds = (int *)malloc((n + 1) * sizeof(int));

  // Initialize LIS and LDS arrays to 1
  for (i = 0; i <= n; ++i)
  {
    lis[i] = 1;
    lds[i] = 1;
  }

  // Compute LIS values from left to right
  for (i = 1; i < n; ++i)
  {
    for (j = 0; j < i; ++j)
    {
      if (arr[i] > arr[j] && lis[i] < lis[j] + 1)
      {
        lis[i] = lis[j] + 1;
      }
    }
  }

  // Compute LDS values from right to left
  for (i = n - 2; i >= 0; --i)
  {
    for (j = n - 1; j > i; --j)
    {
      if (arr[i] > arr[j] && lds[i] < lds[j] + 1)
      {
        lds[i] = lds[j] + 1;
      }
    }
  }

  // Find the maximum value of lis[i] + lds[i] - 1
  maximum = lds[0] + lis[0] - 1;
  for (i = 1; i < n; ++i)
  {
    if (lds[i] + lis[i] - 1 > maximum)
    {
      maximum = lds[i] + lis[i] - 1;
    }
  }

  free(lis);
  free(lds);

  return maximum;
}