bool __cdecl contains_zero_triplet_sum(int *arr, int size)
{
  for (int i = 0; i < size; ++i)
  {
    for (int j = i + 1; j < size; ++j)
    {
      for (int k = j + 1; k < size; ++k)
      {
        if (arr[i] + arr[j] + arr[k] == 0)
          return true;
      }
    }
  }
  return false;
}