int __cdecl func0(int *arr, int n, int m)
{
  // First pass: Normalize each element based on the divisor 'm'.
  // The new value is the quotient of the division, plus 1 if there is a remainder.
  for (int i = 0; i < n; ++i)
  {
    arr[i] = arr[i] / m + (arr[i] % m != 0);
  }

  int max_val = -1;
  int max_idx = -1;

  // Second pass: Iterate backwards to find the last element with the maximum value.
  // By iterating backwards and using strictly less than (<), we naturally 
  // select the last occurrence of the maximum value without needing extra checks.
  for (int i = n - 1; i >= 0; --i)
  {
    if (max_val < arr[i])
    {
      max_val = arr[i];
      max_idx = i;
    }
  }

  // Return the 1-based index
  return max_idx + 1;
}