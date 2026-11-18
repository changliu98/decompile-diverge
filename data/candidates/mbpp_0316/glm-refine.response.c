int __cdecl func0(int *A, int n, int x)
{
  int left = 0;
  int right = n - 1;
  int result = -1;

  while (left <= right)
  {
    int mid = left + (right - left) / 2; // Prevents potential integer overflow and matches standard binary search idiom

    if (x == A[mid])
    {
      result = mid; // Replaced redundant division with 'mid'
      left = mid + 1; // Continues searching the right half to find the last occurrence
    }
    else if (x > A[mid]) // Changed 'x >= A[mid]' to 'x > A[mid]' since equality is already handled above
    {
      left = mid + 1;
    }
    else
    {
      right = mid - 1;
    }
  }
  
  return result;
}