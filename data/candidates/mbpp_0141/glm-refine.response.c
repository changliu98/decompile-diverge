void __cdecl func0(int *arr, int n)
{
  int max_idx; // Index of the maximum element in the current subarray

  // Continue sorting until the unsorted portion of the array is reduced to 1 element
  while (n > 1)
  {
    // Find the index of the maximum element in the unsorted subarray arr[0...n-1]
    max_idx = find_max_index(arr, n);

    // If the maximum element is not already at the end of the unsorted portion
    if (max_idx != n - 1)
    {
      // Flip the subarray arr[0...max_idx] to move the maximum element to the front (index 0)
      reverse(arr, 0, max_idx);

      // Flip the subarray arr[0...n-1] to move the maximum element to its correct sorted position at the end
      reverse(arr, 0, n - 1);
    }

    // Decrease the size of the unsorted subarray
    --n;
  }
}