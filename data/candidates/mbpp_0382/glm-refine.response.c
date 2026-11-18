// This function finds the index of the minimum element in a rotated sorted array.
// It returns the index of the pivot (smallest element), or -1 if not found.
int __cdecl find_pivot_index(int *A, int n)
{
  int left = 0;
  int right = n - 1;

  while ( left <= right )
  {
    // If the subarray is already sorted, the leftmost element is the minimum.
    if ( A[left] <= A[right] )
      return left;

    int mid = left + (right - left) / 2;
    int prev = (mid - 1 + n) % n;
    int next = (mid + 1) % n;

    // Check if the mid element is the minimum element (pivot)
    if ( A[mid] <= A[next] && A[mid] <= A[prev] )
      return mid;

    // Decide whether to search in the left half or the right half
    if ( A[mid] > A[right] )
    {
      // The right half is unsorted, so the pivot must be here.
      // The additional check `A[mid] >= A[left]` is redundant in a standard 
      // rotated binary search but preserved here to maintain exact semantics.
      if ( A[mid] >= A[left] )
        left = mid + 1;
    }
    else
    {
      // The left half is unsorted, or the right half is strictly sorted.
      // The pivot must be in the left half.
      right = mid - 1;
    }
  }

  return -1;
}