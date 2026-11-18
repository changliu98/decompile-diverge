int __cdecl func0(int *nums, int size)
{
  int j;
  int count;
  int i;
  int result;
  int max_count;

  max_count = 0;
  result = nums[0];
  
  for (i = 0; i < size; ++i)
  {
    count = 0;
    for (j = 0; j < size; ++j)
    {
      if (nums[j] == nums[i])
        ++count;
    }
    
    if (count > max_count)
    {
      max_count = count;
      result = nums[i];
    }
  }
  
  return result;
}