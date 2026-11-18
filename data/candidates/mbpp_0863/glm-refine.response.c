int __cdecl func0(int *arr, int n)
{
  int temp;
  int j;
  int i;
  int *unique_arr;
  int unique_count;
  int curr_streak;
  int max_streak;

  max_streak = 0;
  curr_streak = 0;

  // Sort the array using Bubble Sort
  for (i = 0; i < n - 1; ++i)
  {
    for (j = 0; j < n - i - 1; ++j)
    {
      if (arr[j] > arr[j + 1])
      {
        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }

  // Allocate an array to store unique elements
  unique_arr = (int *)malloc(4LL * n);
  unique_count = 1;
  *unique_arr = *arr;

  // Extract unique elements from the sorted array
  for (i = 1; i < n; ++i)
  {
    if (arr[i] != arr[i - 1])
    {
      unique_arr[unique_count++] = arr[i];
    }
  }

  // Find the length of the longest consecutive sequence
  for (i = 0; i < unique_count; ++i)
  {
    if (i > 0 && unique_arr[i] == unique_arr[i - 1] + 1)
    {
      ++curr_streak;
    }
    else
    {
      curr_streak = 1;
    }

    if (max_streak < curr_streak)
    {
      max_streak = curr_streak;
    }
  }

  free(unique_arr);
  return max_streak;
}