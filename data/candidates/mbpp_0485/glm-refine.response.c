int __cdecl func0(int *A, int n)
{
  int temp;
  int i, j;

  // Sort the array in ascending order using an exchange (bubble-like) sort
  for (i = 0; i < n; ++i)
  {
    for (j = i + 1; j < n; ++j)
    {
      if (A[i] > A[j])
      {
        temp = A[i];
        A[i] = A[j];
        A[j] = temp;
      }
    }
  }

  // Traverse the sorted array backwards (from largest to smallest)
  for (i = n - 1; i >= 0; --i)
  {
    // Return the largest element that is a palindrome
    if (is_palindrome(A[i]))
      return A[i];
  }

  // Return -1 if no palindromic elements are found
  return -1;
}