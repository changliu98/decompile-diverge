void __cdecl func0(int *l, int size, int *out)
{
  int temp;
  int min_idx;
  int third_size;
  int i, k, ib;
  int *third;

  // Allocate memory for every 3rd element
  third = (int *)malloc(sizeof(int) * (size / 3 + 1));
  third_size = 0;
  
  // Extract every 3rd element into the 'third' array
  for (i = 0; 3 * i < size; ++i)
  {
    third[i] = l[3 * i];
    ++third_size;
  }

  // Sort the 'third' array using Selection Sort
  for (i = 0; i < third_size - 1; ++i)
  {
    min_idx = i;
    for (k = i + 1; k < third_size; ++k)
    {
      if (third[k] < third[min_idx])
      {
        min_idx = k;
      }
    }
    
    if (min_idx != i)
    {
      temp = third[i];
      third[i] = third[min_idx];
      third[min_idx] = temp;
    }
  }

  // Construct the output array
  for (ib = 0; ib < size; ++ib)
  {
    if (ib % 3 == 0)
    {
      // If index is a multiple of 3, take the sorted value
      out[ib] = third[ib / 3];
    }
    else
    {
      // Otherwise, take the original unsorted value
      out[ib] = l[ib];
    }
  }

  free(third);
}