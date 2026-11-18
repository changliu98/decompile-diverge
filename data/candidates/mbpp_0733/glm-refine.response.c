int __cdecl func0(int *A, int n, int x)
{
  int left = 0;
  int right = n - 1;
  int result = -1;

  while (left <= right)
  {
    int mid = left + (right - left) / 2;

    if (x == A[mid])
    {
      result = mid;
      right = mid - 1;  // Continue searching in the left half to find the first occurrence
    }
    else if (x > A[mid])
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