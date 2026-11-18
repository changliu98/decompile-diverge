int __cdecl func0(int *nums, int size)
{
  int i;
  int min_val;
  int max_val;

  max_val = INT_MIN;
  min_val = INT_MAX;
  
  for ( i = 0; i < size; ++i )
  {
    if ( nums[i] > max_val )
      max_val = nums[i];
    if ( nums[i] < min_val )
      min_val = nums[i];
  }
  
  return max_val - min_val;
}