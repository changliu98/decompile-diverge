void __cdecl func0(const int *test_list, int n, int *result)
{
  // The last element of the source array becomes the first element of the result array.
  result[0] = test_list[n - 1];

  // Shift the remaining elements to the right by one index.
  // Using pointer arithmetic to eliminate the need for a loop counter variable.
  for (int i = 1; i < n; ++i)
  {
    result[i] = test_list[i - 1];
  }
}