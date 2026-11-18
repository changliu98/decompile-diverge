void func0(int *nums, int nums_size, int count, int *result)
{
  // Sort the input array in ascending order
  qsort(nums, nums_size, sizeof(int), compare);
  
  // Copy the first 'count' elements from the sorted array to the result array
  for (int i = 0; i < count; ++i)
  {
    result[i] = nums[i];
  }
}