bool __cdecl is_sorted_and_rotated(int *arr, int size)
{
  if (size == 0)
    return true;

  int drop_count = 0;

  for (int i = 1; i < size; ++i)
  {
    if (arr[i] < arr[i - 1])
      ++drop_count;
  }

  // Check the wrap-around boundary
  if (arr[size - 1] > arr[0])
    ++drop_count;

  // A sorted and rotated array can have at most 1 drop
  return drop_count < 2;
}