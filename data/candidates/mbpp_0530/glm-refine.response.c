double __cdecl func0(int *nums, int n)
{
  int negative_count = 0;

  for (int i = 0; i < n; ++i)
  {
    if (nums[i] < 0)
      ++negative_count;
  }

  // Calculate the percentage of negative numbers and round it to 2 decimal places
  return round(100.0 * ((double)negative_count / (double)n)) / 100.0;
}