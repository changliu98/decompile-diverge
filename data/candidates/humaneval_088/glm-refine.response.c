void __cdecl func0(int *array, int size, int **out_array, int *out_size)
{
  int i, j;
  int *copy;

  *out_size = size;

  if (size == 0)
  {
    *out_array = NULL;
    return;
  }

  // Allocate memory for the copied array
  copy = (int *)malloc(sizeof(int) * size);
  if (!copy)
    exit(1);
    
  *out_array = copy;

  // Copy the original array into the newly allocated memory
  for (i = 0; i < size; ++i)
    copy[i] = array[i];

  // Determine sort order: ascending if the sum of the first and last 
  // elements is odd, descending otherwise.
  int sort_ascending = ((array[0] + array[size - 1]) % 2 == 1);

  // Bubble sort the copied array
  for (i = 0; i < size - 1; ++i)
  {
    for (j = i + 1; j < size; ++j)
    {
      int needs_swap = sort_ascending 
          ? (copy[i] > copy[j]) 
          : (copy[i] < copy[j]);

      if (needs_swap)
      {
        int temp = copy[i];
        copy[i] = copy[j];
        copy[j] = temp;
      }
    }
  }
}