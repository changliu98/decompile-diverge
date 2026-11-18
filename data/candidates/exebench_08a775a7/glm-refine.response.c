int __cdecl next(int *mask, int n)
{
  int i;

  // Find the first non-zero element in the array
  for (i = 0; i < n && mask[i] != 0; ++i)
  {
    mask[i] = 0; // Reset to 0 (carry over)
  }

  // If we reached the end of the array, it means all elements were non-zero
  if (i >= n)
    return 0; // Overflow / no more states

  // Set the current element to 1
  mask[i] = 1;
  return 1; // Success
}