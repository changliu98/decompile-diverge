// Sorts the array using a basic selection sort, then calculates the median.
float __cdecl get_median(float *arr, int size)
{
  float temp; // Temporary variable for swapping
  int j;
  int i;

  // Sort the array in ascending order
  for (i = 0; i < size; ++i)
  {
    for (j = i + 1; j < size; ++j)
    {
      if (arr[i] > arr[j])
      {
        // Swap arr[i] and arr[j]
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
  }

  // Calculate and return the median
  if (size % 2 == 1)
  {
    // Odd number of elements: return the middle one
    return arr[size / 2];
  }
  
  // Even number of elements: return the average of the two middle ones
  return 0.5f * (arr[size / 2] + arr[size / 2 - 1]);
}