bool __cdecl is_unique(int *arr, int length)
{
  for (int i = 0; i < length; ++i)
  {
    for (int j = i + 1; j < length; ++j)
    {
      if (arr[i] == arr[j])
        return false;
    }
  }
  return true;
}