int __cdecl func0(int *A, int left, int right)
{
  int mid;

  // Base case: if the search range is invalid, return the lower bound.
  // This happens when the target index is not found within the array bounds.
  if (left > right)
    return left;

  // Calculate the midpoint, avoiding potential integer overflow
  mid = left + (right - left) / 2;

  // If the middle element matches its index, the mismatch must be to the right.
  if (A[mid] == mid)
    return func0(A, mid + 1, right);
  // Otherwise, the mismatch is at 'mid' or to its left.
  else
    return func0(A, left, mid - 1);
}