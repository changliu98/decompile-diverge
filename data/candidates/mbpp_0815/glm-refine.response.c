void __cdecl dutch_national_flag_sort(int *arr, int n)
{
  int low = 0;
  int mid = 0;
  int high = n - 1;

  while (mid <= high)
  {
    if (arr[mid] == 0)
    {
      // Swap arr[low] and arr[mid], then advance both pointers
      int temp = arr[low];
      arr[low] = arr[mid];
      arr[mid] = temp;
      ++low;
      ++mid;
    }
    else if (arr[mid] == 1)
    {
      // Element is already in the correct middle partition
      ++mid;
    }
    else // arr[mid] == 2
    {
      // Swap arr[mid] and arr[high], then shrink the high partition
      int temp = arr[mid];
      arr[mid] = arr[high];
      arr[high] = temp;
      --high;
    }
  }
}