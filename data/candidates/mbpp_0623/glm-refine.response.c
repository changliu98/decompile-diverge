void __cdecl func0(int *nums, int length, int n, int *result)
{
  // Iterate over each element up to the given length
  for (int i = 0; i < length; ++i)
  {
    // Casts to double are implicit for `pow` but kept explicit here to match 
    // the original assembly behavior and highlight the type promotion.
    result[i] = (int)pow((double)nums[i], (double)n);
  }
}