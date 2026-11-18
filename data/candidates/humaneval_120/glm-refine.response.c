void __cdecl func0(int *arr, int arr_size, int k, int *out)
{
  int temp;
  int i, j;

  // Sort the array in ascending order using Bubble Sort
  for (i = 0; i < arr_size - 1; ++i)
  {
    for (j = 0; j < arr_size - i - 1; ++j)
    {
      if (arr[j] > arr[j + 1])
      {
        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }

  // Copy the k largest elements from the end of the sorted array
  for (i = 0; i < k; ++i)
  {
    out[i] = arr[i + arr_size - k];
  }
}