int __cdecl func0(int *arr, int n)
{
  // Wrapper function to initiate the peak-finding algorithm.
  // It sets up the initial search boundaries for the entire array.
  return find_peak_util(arr, 0, n - 1, n);
}