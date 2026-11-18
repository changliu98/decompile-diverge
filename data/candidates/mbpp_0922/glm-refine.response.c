void __cdecl find_max_product_pair(int *arr, int arr_len, int *out_x, int *out_y)
{
  if (arr_len < 2)
  {
    *out_x = 0;
    *out_y = 0;
    return;
  }

  // Initialize with the product of the first two elements
  *out_x = arr[0];
  *out_y = arr[1];

  // Iterate over all unique pairs (i, j) where j > i
  for (int i = 0; i < arr_len; ++i)
  {
    for (int j = i + 1; j < arr_len; ++j)
    {
      // If the product of the current pair is strictly greater than the saved maximum
      if (arr[j] * arr[i] > *out_y * *out_x)
      {
        *out_x = arr[i];
        *out_y = arr[j];
      }
    }
  }
}