int __cdecl func0(int *arr, int n)
{
  // Iterate through the array starting from the second element (index 1)
  for (int i = 1; i < n; ++i)
  {
    // If the current element is strictly less than the previous element,
    // the array is not sorted in non-decreasing order. Return its index.
    if (arr[i] < arr[i - 1])
      return i;
  }
  
  // If the loop completes without returning, the array is fully sorted.
  // Return 0 to indicate no out-of-order element was found.
  return 0;
}