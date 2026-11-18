int __cdecl func0(int *arr, int x, int n)
{
  int low = 0;
  int high = n - 1;
  int res = -1;

  while (low <= high)
  {
    int mid = low + (high - low) / 2; // Optimized to prevent potential overflow and matches standard binary search

    if (arr[mid] < x)
    {
      low = mid + 1;
    }
    else if (arr[mid] > x)
    {
      high = mid - 1;
    }
    else // arr[mid] == x
    {
      res = mid;
      low = mid + 1; // Continues searching to the right
    }
  }
  
  return res;
}