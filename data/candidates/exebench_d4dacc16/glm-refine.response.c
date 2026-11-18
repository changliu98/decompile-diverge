void __cdecl findMinMax(long *nums, long *min, long *max)
{
  // Iterate from index 1 to 4 (total of 4 iterations)
  for (int i = 1; i < 5; ++i)
  {
    // Update min if the current element is smaller
    if (nums[i] < *min)
      *min = nums[i];
      
    // Update max if the current element is larger
    if (nums[i] > *max)
      *max = nums[i];
  }
}