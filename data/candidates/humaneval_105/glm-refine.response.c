void __cdecl func0(int *arr, int size, char ***out, int *out_size)
{
  char *names[10];
  int temp;
  int i, j;
  int out_idx;
  
  // Load the global array of 10 string pointers
  memcpy(names, &off_3D90, sizeof(names));

  // Standard Bubble Sort (ascending order)
  for (i = 0; i < size - 1; ++i)
  {
    for (j = 0; j < size - i - 1; ++j)
    {
      if (arr[j] > arr[j + 1])
      {
        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }

  // Count how many elements are in the range [1, 9]
  *out_size = 0;
  for (i = size - 1; i >= 0; --i)
  {
    if (arr[i] >= 1 && arr[i] <= 9)
      ++(*out_size);
  }

  // Allocate an array of string pointers for the output
  *out = (char **)malloc(8LL * *out_size);

  // Iterate backwards through the sorted array and map numbers 1-9 to strings
  out_idx = 0;
  for (i = size - 1; i >= 0 && out_idx < *out_size; --i)
  {
    if (arr[i] >= 1 && arr[i] <= 9)
    {
      (*out)[out_idx++] = names[arr[i]];
    }
  }
}