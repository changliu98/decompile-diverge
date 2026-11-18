int *__cdecl func0(int *arr, int size, int *out_size)
{
  int *out = (int *)malloc(4LL * size);
  int out_count = 0;
  
  // Remove duplicates
  for (int i = 0; i < size; ++i)
  {
    int found = 0;
    for (int j = 0; j < out_count; ++j)
    {
      if (arr[i] == out[j])
      {
        found = 1;
        break;
      }
    }
    if (!found)
    {
      out[out_count++] = arr[i];
    }
  }
  
  // Sort the unique elements (Bubble Sort)
  for (int i = 0; i < out_count - 1; ++i)
  {
    for (int j = i + 1; j < out_count; ++j)
    {
      if (out[i] > out[j])
      {
        int temp = out[i];
        out[i] = out[j];
        out[j] = temp;
      }
    }
  }
  
  *out_size = out_count;
  return out;
}