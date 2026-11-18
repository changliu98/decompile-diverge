double __cdecl func0(int *nums, int n)
{
  int zero_count = 0;

  // Count the number of zeros in the array
  for (int i = 0; i < n; ++i)
  {
    if (nums[i] == 0)
      ++zero_count;
  }

  // Calculate the percentage and round to 2 decimal places
  return round(100.0 * ((double)zero_count / (double)n)) / 100.0;
}