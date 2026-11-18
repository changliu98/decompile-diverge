int __cdecl func0(int *arr, int target, int size)
{
  int low = 0;
  int high = size - 1;
  int result = -1;

  while (low <= high)
  {
    int mid = (high + low) / 2;

    if (arr[mid] == target)
    {
      result = mid;
      high = mid - 1; // Continue searching the left half for an earlier occurrence
    }
    else if (arr[mid] < target)
    {
      low = mid + 1;
    }
    else
    {
      high = mid - 1;
    }
  }

  return result;
}