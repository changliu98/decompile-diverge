void __cdecl func0(float *l, int size, float *out)
{
  float swap_temp;
  int num_evens;
  int i, j;
  float *even;

  // Allocate space for even-indexed elements (plus 1 to be safe for odd sizes)
  even = (float *)malloc(4LL * (size / 2 + 1));
  num_evens = 0;
  
  // Extract elements at even indices (0, 2, 4, ...)
  for (i = 0; i < size; i += 2)
  {
    even[num_evens] = l[i];
    num_evens++;
  }
  
  // Sort the extracted even-indexed elements using Bubble Sort
  for (i = 0; i < num_evens - 1; ++i)
  {
    for (j = 0; j < num_evens - i - 1; ++j)
    {
      if (even[j] > even[j + 1])
      {
        swap_temp = even[j];
        even[j] = even[j + 1];
        even[j + 1] = swap_temp;
      }
    }
  }
  
  // Reconstruct the output array
  for (i = 0; i < size; ++i)
  {
    // If index is odd, keep the original value. 
    // If index is even, use the sorted value.
    out[i] = (i % 2 != 0) ? l[i] : even[i / 2];
  }
  
  free(even);
}