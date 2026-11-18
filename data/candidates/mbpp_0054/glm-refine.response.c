void __cdecl func0(int *arr, int n)
{
  int max_val = 0;
  
  // Find the maximum value in the array
  for (int i = 0; i < n; ++i)
  {
    if (arr[i] > max_val)
      max_val = arr[i];
  }

  // Allocate and initialize the counting buckets
  int *counts = (int *)malloc(sizeof(int) * (max_val + 1));
  for (int i = 0; i <= max_val; ++i)
    counts[i] = 0;

  // Count the occurrences of each element in the array
  for (int i = 0; i < n; ++i)
    counts[arr[i]]++;

  // Overwrite the original array with sorted values
  int pos = 0;
  for (int i = 0; i <= max_val; ++i)
  {
    for (int j = 0; j < counts[i]; ++j)
      arr[pos++] = i;
  }

  free(counts);
}