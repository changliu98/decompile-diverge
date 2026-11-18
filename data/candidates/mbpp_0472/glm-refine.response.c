bool __cdecl func0(int *l, int size)
{
  int *sorted = (int *)malloc(4LL * size);
  
  // Copy the original array
  for (int i = 0; i < size; ++i)
    sorted[i] = l[i];

  // Sort the copied array using an exchange (selection-like) sort
  for (int i = 0; i < size; ++i)
  {
    for (int j = i + 1; j < size; ++j)
    {
      if (sorted[i] > sorted[j])
      {
        int temp = sorted[i];
        sorted[i] = sorted[j];
        sorted[j] = temp;
      }
    }
  }

  // Check if the sorted array contains consecutive numbers
  bool result = true;
  for (int i = 1; i < size; ++i)
  {
    if (sorted[i] != sorted[i - 1] + 1)
    {
      result = false;
      break;
    }
  }

  free(sorted);
  return result;
}