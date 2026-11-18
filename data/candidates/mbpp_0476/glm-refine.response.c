int __cdecl func0(int *nums, int size)
{
  int min_num = INT_MAX;
  int max_num = INT_MIN;
  
  for (int i = 0; i < size; ++i)
  {
    if (nums[i] > max_num)
      max_num = nums[i];
    if (nums[i] < min_num)
      min_num = nums[i];
  }
  
  return min_num + max_num;
}