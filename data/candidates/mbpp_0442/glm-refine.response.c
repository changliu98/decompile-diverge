double __cdecl func0(int *nums, int n)
{
  int positive_count = 0;

  for (int i = 0; i < n; ++i)
  {
    if (nums[i] > 0)
      ++positive_count;
  }

  return round(100.0 * ((double)positive_count / (double)n)) / 100.0;
}